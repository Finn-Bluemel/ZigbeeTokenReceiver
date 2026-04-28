#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Tickable.h"
#include "TokenData.h"
#include "TokenDataSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTokenReceived, const FTokenData&, Data);

/**
 * GameInstance subsystem — opens a USB serial port and fires OnTokenReceived
 * on the game thread for every valid token message received.
 *
 * Blueprint usage:
 *   1. Get Game Instance Subsystem (TokenDataSubsystem)
 *   2. Call AutoOpenPort() — finds the receiver ESP32-C6 automatically
 *   3. Bind event to OnTokenReceived
 *   4. Read FTokenData fields (Timestamp, TokenId, Sensor0–3, BatteryMv)
 */
UCLASS()
class TOKENRECEIVER_API UTokenDataSubsystem : public UGameInstanceSubsystem, public FTickableGameObject
{
    GENERATED_BODY()

public:
    // Fired on the game thread for each received token message
    UPROPERTY(BlueprintAssignable, Category = "Token")
    FOnTokenReceived OnTokenReceived;

    /** Scan for an Espressif USB device (VID 0x303A) and open it automatically. */
    UFUNCTION(BlueprintCallable, Category = "Token")
    void AutoOpenPort(int32 BaudRate = 115200);

    /** Open a specific port by name, e.g. "COM16". Fallback if auto-detect fails. */
    UFUNCTION(BlueprintCallable, Category = "Token")
    void OpenPort(const FString& PortName, int32 BaudRate = 115200);

    /** Close the serial port. Called automatically on subsystem shutdown. */
    UFUNCTION(BlueprintCallable, Category = "Token")
    void ClosePort();

    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Token")
    bool IsConnected() const { return bConnected; }

    // USubsystem
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;

    // FTickableGameObject — dispatches queued messages on the game thread
    virtual void    Tick(float DeltaTime) override;
    virtual TStatId GetStatId() const override { RETURN_QUICK_DECLARE_CYCLE_STAT(UTokenDataSubsystem, STATGROUP_Tickables); }
    virtual bool    IsTickable() const override { return !IsTemplate() && bConnected; }

private:
    bool bConnected = false;

    TQueue<FTokenData, EQueueMode::Mpsc> MessageQueue;

    class FSerialReader* ReaderThread = nullptr;
    FRunnableThread*     Thread       = nullptr;
};
