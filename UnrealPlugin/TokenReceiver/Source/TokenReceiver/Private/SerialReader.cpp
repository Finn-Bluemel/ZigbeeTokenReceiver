#include "SerialReader.h"
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

    // "TOKEN 436135512 [1 2 3 4] batt:3600mV"
    // Simple token-by-token parse — avoids UE5 regex engine quirks.
    int32 TokenPos = Line.Find(TEXT("TOKEN "), ESearchCase::CaseSensitive);
    if (TokenPos != INDEX_NONE)
    {
        // Parse chip id — everything between "TOKEN " and the next space
        int32 IdStart = TokenPos + 6; // skip "TOKEN "
        int32 IdEnd   = Line.Find(TEXT(" "), ESearchCase::CaseSensitive, ESearchDir::FromStart, IdStart);
        if (IdEnd != INDEX_NONE)
        {
            Data.TokenId = FCString::Atoi(*Line.Mid(IdStart, IdEnd - IdStart));
        }

        // Parse slot values — between "[" and "]" after the chip id
        int32 BracketOpen  = Line.Find(TEXT("["), ESearchCase::CaseSensitive, ESearchDir::FromStart, IdEnd);
        int32 BracketClose = Line.Find(TEXT("]"), ESearchCase::CaseSensitive, ESearchDir::FromStart, BracketOpen + 1);
        if (BracketOpen != INDEX_NONE && BracketClose > BracketOpen)
        {
            FString Inner = Line.Mid(BracketOpen + 1, BracketClose - BracketOpen - 1).TrimStartAndEnd();
            TArray<FString> Parts;
            Inner.ParseIntoArray(Parts, TEXT(" "), true);
            if (Parts.Num() >= 4)
            {
                Data.Slot0 = FCString::Atoi(*Parts[0]);
                Data.Slot1 = FCString::Atoi(*Parts[1]);
                Data.Slot2 = FCString::Atoi(*Parts[2]);
                Data.Slot3 = FCString::Atoi(*Parts[3]);
            }
        }

        // Parse battery — between "batt:" and "mV"
        int32 BattStart = Line.Find(TEXT("batt:"), ESearchCase::CaseSensitive, ESearchDir::FromStart, BracketClose);
        int32 MvPos     = Line.Find(TEXT("mV"),   ESearchCase::CaseSensitive, ESearchDir::FromStart, BattStart);
        if (BattStart != INDEX_NONE && MvPos > BattStart)
        {
            int32 NumStart = BattStart + 5; // skip "batt:"
            Data.BatteryMv = FCString::Atoi(*Line.Mid(NumStart, MvPos - NumStart));
        }
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
