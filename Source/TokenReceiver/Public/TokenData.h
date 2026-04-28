#pragma once
#include "CoreMinimal.h"
#include "TokenData.generated.h"

USTRUCT(BlueprintType)
struct TOKENRECEIVER_API FTokenData
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly, Category = "Token")
    FString RawMessage;

    UPROPERTY(BlueprintReadOnly, Category = "Token")
    FString Timestamp;

    UPROPERTY(BlueprintReadOnly, Category = "Token")
    int32 TokenId = 0;

    UPROPERTY(BlueprintReadOnly, Category = "Token")
    int32 Sensor0 = 0;

    UPROPERTY(BlueprintReadOnly, Category = "Token")
    int32 Sensor1 = 0;

    UPROPERTY(BlueprintReadOnly, Category = "Token")
    int32 Sensor2 = 0;

    UPROPERTY(BlueprintReadOnly, Category = "Token")
    int32 Sensor3 = 0;

    UPROPERTY(BlueprintReadOnly, Category = "Token")
    int32 BatteryMv = 0;
};
