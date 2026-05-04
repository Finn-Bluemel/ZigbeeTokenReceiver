#pragma once

#include "CoreMinimal.h"
#include "HAL/Runnable.h"
#include "TokenData.h"

/**
 * Background thread: opens a Windows COM port, reads lines, parses them
 * into FTokenData, and pushes them onto a caller-owned TQueue.
 */
class FSerialReader : public FRunnable
{
public:
    explicit FSerialReader(TQueue<FTokenData, EQueueMode::Mpsc>* InQueue)
        : Queue(InQueue) {}

    /** Returns true if the port opened successfully. */
    bool Open(const FString& PortName, int32 BaudRate);

    void Close();

    bool IsOpen() const;

    // FRunnable
    virtual uint32 Run() override;
    virtual void   Stop() override;

private:
    static FTokenData ParseLine(const FString& Line);

    TQueue<FTokenData, EQueueMode::Mpsc>* Queue = nullptr;
    volatile bool bRunning = false;

    FString LineAccum;

#if PLATFORM_WINDOWS
    void* hComm = nullptr;   // HANDLE, kept as void* to avoid including Windows.h in this header
#endif
};
