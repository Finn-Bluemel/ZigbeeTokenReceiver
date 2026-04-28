#include "SerialReader.h"
#include "Internationalization/Regex.h"
#include "Misc/Char.h"

#if PLATFORM_WINDOWS
#include "Windows/AllowWindowsPlatformTypes.h"
#include <windows.h>
#include "Windows/HideWindowsPlatformTypes.h"
#endif

// ── Open / Close ──────────────────────────────────────────────────────────────

bool FSerialReader::Open(const FString& PortName, int32 BaudRate)
{
#if PLATFORM_WINDOWS
    // Prefix with \\.\\ to support COM ports above COM9
    FString FullPath = FString::Printf(TEXT("\\\\.\\%s"), *PortName);

    HANDLE Handle = CreateFile(
        *FullPath,
        GENERIC_READ,
        0,
        nullptr,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        nullptr
    );

    if (Handle == INVALID_HANDLE_VALUE)
    {
        UE_LOG(LogTemp, Error, TEXT("TokenReceiver: failed to open %s (error %d)"), *PortName, GetLastError());
        return false;
    }

    DCB dcb = {};
    dcb.DCBlength = sizeof(DCB);
    GetCommState(Handle, &dcb);
    dcb.BaudRate = BaudRate;
    dcb.ByteSize = 8;
    dcb.StopBits = ONESTOPBIT;
    dcb.Parity   = NOPARITY;
    SetCommState(Handle, &dcb);

    // Non-blocking reads: return after 50 ms even if no bytes arrived
    COMMTIMEOUTS timeouts = {};
    timeouts.ReadIntervalTimeout        = 10;
    timeouts.ReadTotalTimeoutMultiplier = 0;
    timeouts.ReadTotalTimeoutConstant   = 50;
    SetCommTimeouts(Handle, &timeouts);

    hComm    = Handle;
    bRunning = true;
    return true;

#else
    UE_LOG(LogTemp, Warning, TEXT("TokenReceiver: serial port access not implemented on this platform"));
    return false;
#endif
}

void FSerialReader::Close()
{
    bRunning = false;
#if PLATFORM_WINDOWS
    if (hComm && hComm != (void*)INVALID_HANDLE_VALUE)
    {
        CloseHandle((HANDLE)hComm);
        hComm = nullptr;
    }
#endif
}

bool FSerialReader::IsOpen() const
{
#if PLATFORM_WINDOWS
    return hComm && hComm != (void*)INVALID_HANDLE_VALUE;
#else
    return false;
#endif
}

// ── Parsing ───────────────────────────────────────────────────────────────────

FTokenData FSerialReader::ParseLine(const FString& Line)
{
    FTokenData Data;
    Data.RawMessage = Line;

    // "2026/04/28 11:33:39 [2079928368] [0 1 0 2] batt:3603mV"
    static const FRegexPattern Pat(
        TEXT(R"((\d{4}/\d{2}/\d{2} \d{2}:\d{2}:\d{2})\s+\[(\d+)\]\s+\[(\d+) (\d+) (\d+) (\d+)\]\s+batt:(\d+)mV)")
    );

    FRegexMatcher M(Pat, Line);
    if (M.FindNext())
    {
        Data.Timestamp  = M.GetCaptureGroup(1);
        Data.TokenId    = FCString::Atoi(*M.GetCaptureGroup(2));
        Data.Sensor0    = FCString::Atoi(*M.GetCaptureGroup(3));
        Data.Sensor1    = FCString::Atoi(*M.GetCaptureGroup(4));
        Data.Sensor2    = FCString::Atoi(*M.GetCaptureGroup(5));
        Data.Sensor3    = FCString::Atoi(*M.GetCaptureGroup(6));
        Data.BatteryMv  = FCString::Atoi(*M.GetCaptureGroup(7));
    }

    return Data;
}

// ── FRunnable ─────────────────────────────────────────────────────────────────

uint32 FSerialReader::Run()
{
#if PLATFORM_WINDOWS
    uint8 Buf[256];
    DWORD BytesRead = 0;

    while (bRunning)
    {
        if (!ReadFile((HANDLE)hComm, Buf, sizeof(Buf), &BytesRead, nullptr))
        {
            UE_LOG(LogTemp, Warning, TEXT("TokenReceiver: ReadFile error %d, closing"), GetLastError());
            break;
        }

        for (DWORD i = 0; i < BytesRead; ++i)
        {
            const char C = static_cast<char>(Buf[i]);
            if (C == '\n')
            {
                LineAccum.TrimEndInline();
                // Ignore diagnostic lines printed by the firmware
                if (LineAccum.Len() > 0 && !LineAccum.StartsWith(TEXT("[receiver]")))
                {
                    FTokenData Data = ParseLine(LineAccum);
                    Queue->Enqueue(Data);
                }
                LineAccum.Empty();
            }
            else if (C != '\r')
            {
                LineAccum.AppendChar(static_cast<TCHAR>(C));
            }
        }
    }
#endif
    return 0;
}

void FSerialReader::Stop()
{
    bRunning = false;
}
