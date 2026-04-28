#include "TokenDataSubsystem.h"
#include "SerialReader.h"
#include "HAL/RunnableThread.h"

#if PLATFORM_WINDOWS
#include "Windows/AllowWindowsPlatformTypes.h"
#include <windows.h>
#include <setupapi.h>
#include "Windows/HideWindowsPlatformTypes.h"
#endif

// ── Auto-detect ───────────────────────────────────────────────────────────────

#if PLATFORM_WINDOWS
/** Walk the system's serial port devices and return the first one whose
 *  hardware ID contains VID_303A (Espressif — the ESP32-C6 USB CDC). */
static FString FindEspressifPort()
{
    // GUID_DEVCLASS_PORTS  {4D36E978-E325-11CE-BFC1-08002BE10318}
    const GUID PortsGuid = { 0x4D36E978, 0xE325, 0x11CE,
        { 0xBF, 0xC1, 0x08, 0x00, 0x2B, 0xE1, 0x03, 0x18 } };

    HDEVINFO DevInfo = SetupDiGetClassDevs(&PortsGuid, nullptr, nullptr, DIGCF_PRESENT);
    if (DevInfo == INVALID_HANDLE_VALUE) return {};

    FString Result;
    SP_DEVINFO_DATA DevData = {};
    DevData.cbSize = sizeof(SP_DEVINFO_DATA);

    for (DWORD i = 0; SetupDiEnumDeviceInfo(DevInfo, i, &DevData); ++i)
    {
        TCHAR HwId[1024] = {};
        if (!SetupDiGetDeviceRegistryProperty(DevInfo, &DevData, SPDRP_HARDWAREID,
            nullptr, reinterpret_cast<PBYTE>(HwId), sizeof(HwId), nullptr))
            continue;

        if (!FCString::Stristr(HwId, TEXT("VID_303A")))
            continue;

        // Friendly name looks like "USB Serial Device (COM16)"
        TCHAR Friendly[256] = {};
        if (!SetupDiGetDeviceRegistryProperty(DevInfo, &DevData, SPDRP_FRIENDLYNAME,
            nullptr, reinterpret_cast<PBYTE>(Friendly), sizeof(Friendly), nullptr))
            continue;

        const FString Name(Friendly);
        int32 Open = INDEX_NONE, Close = INDEX_NONE;
        Name.FindLastChar(TEXT('('), Open);
        Name.FindLastChar(TEXT(')'), Close);
        if (Open != INDEX_NONE && Close > Open)
        {
            Result = Name.Mid(Open + 1, Close - Open - 1);
            break;
        }
    }

    SetupDiDestroyDeviceInfoList(DevInfo);
    return Result;
}
#endif

// ── Lifecycle ─────────────────────────────────────────────────────────────────

void UTokenDataSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);
}

void UTokenDataSubsystem::Deinitialize()
{
    ClosePort();
    Super::Deinitialize();
}

// ── Port management ───────────────────────────────────────────────────────────

void UTokenDataSubsystem::AutoOpenPort(int32 BaudRate)
{
#if PLATFORM_WINDOWS
    const FString Port = FindEspressifPort();
    if (Port.IsEmpty())
    {
        UE_LOG(LogTemp, Warning, TEXT("TokenReceiver: no Espressif device found — is the receiver plugged in?"));
        return;
    }
    UE_LOG(LogTemp, Log, TEXT("TokenReceiver: auto-detected %s"), *Port);
    OpenPort(Port, BaudRate);
#else
    UE_LOG(LogTemp, Warning, TEXT("TokenReceiver: AutoOpenPort is Windows-only"));
#endif
}

void UTokenDataSubsystem::OpenPort(const FString& PortName, int32 BaudRate)
{
    ClosePort();

    ReaderThread = new FSerialReader(&MessageQueue);
    if (!ReaderThread->Open(PortName, BaudRate))
    {
        delete ReaderThread;
        ReaderThread = nullptr;
        return;
    }

    Thread     = FRunnableThread::Create(ReaderThread, TEXT("TokenSerialReader"), 0, TPri_BelowNormal);
    bConnected = true;

    UE_LOG(LogTemp, Log, TEXT("TokenReceiver: opened %s @ %d baud"), *PortName, BaudRate);
}

void UTokenDataSubsystem::ClosePort()
{
    if (ReaderThread) ReaderThread->Stop();
    if (Thread)
    {
        Thread->Kill(true);
        delete Thread;
        Thread = nullptr;
    }
    if (ReaderThread)
    {
        ReaderThread->Close();   // CloseHandle(hComm) — release the port before delete
        delete ReaderThread;
        ReaderThread = nullptr;
    }
    bConnected = false;
}

// ── FTickableGameObject ───────────────────────────────────────────────────────

void UTokenDataSubsystem::Tick(float /*DeltaTime*/)
{
    FTokenData Data;
    while (MessageQueue.Dequeue(Data))
    {
        OnTokenReceived.Broadcast(Data);
    }
}
