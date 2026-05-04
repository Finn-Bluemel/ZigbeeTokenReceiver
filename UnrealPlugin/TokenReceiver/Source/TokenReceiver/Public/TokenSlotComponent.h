#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TokenDataSubsystem.h"
#include "TokenSlotComponent.generated.h"

// Fires once per token message with all 4 sensor values — mirrors the old OSC message layout
DECLARE_DYNAMIC_MULTICAST_DELEGATE_SixParams(FOnTokenData,
    int32, TokenId,
    int32, Slot0,
    int32, Slot1,
    int32, Slot2,
    int32, Slot3,
    int32, BatteryMv);

UCLASS(ClassGroup=("Token"), meta=(BlueprintSpawnableComponent))
class TOKENRECEIVER_API UTokenSlotComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UTokenSlotComponent();

    // Fires once per token reading with all 4 slot values (0=empty, 1-4=coral type)
    UPROPERTY(BlueprintAssignable, Category="Token")
    FOnTokenData OnTokenData;

    // -1 = fire for every token. Set to a specific ID to only receive data for that token.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Token")
    int32 FilterTokenId = -1;

    // Set before BeginPlay (or call OpenPort/StartDummyMode manually)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Token")
    int32 BaudRate = 115200;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Token")
    bool bAutoDetectPort = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Token")
    bool bStartDummyIfNoDevice = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Token")
    float DummyInterval = 1.0f;

protected:
    virtual void BeginPlay() override;

private:
    UFUNCTION()
    void HandleTokenReceived(const FTokenData& Data);
};
