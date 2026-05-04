#pragma once
#include "CoreMinimal.h"
#include "TokenData.generated.h"

USTRUCT(BlueprintType)
struct TOKENRECEIVER_API FTokenData
{
    GENERATED_BODY()

    /** Full raw line from serial */
    UPROPERTY(BlueprintReadOnly, Category = "Token")
    FString RawMessage;

    /** Unique chip ID of the sender board */
    UPROPERTY(BlueprintReadOnly, Category = "Token")
    int32 TokenId = 0;

    /** Slot number written to the DS2431 EEPROM in connector SS1 (0 = empty) */
    UPROPERTY(BlueprintReadOnly, Category = "Token")
    int32 Slot0 = 0;

    /** Slot number written to the DS2431 EEPROM in connector SS2 (0 = empty) */
    UPROPERTY(BlueprintReadOnly, Category = "Token")
    int32 Slot1 = 0;

    /** Slot number written to the DS2431 EEPROM in connector SS3 (0 = empty) */
    UPROPERTY(BlueprintReadOnly, Category = "Token")
    int32 Slot2 = 0;

    /** Slot number written to the DS2431 EEPROM in connector SS4 (0 = empty) */
    UPROPERTY(BlueprintReadOnly, Category = "Token")
    int32 Slot3 = 0;

    /** Battery voltage in millivolts */
    UPROPERTY(BlueprintReadOnly, Category = "Token")
    int32 BatteryMv = 0;
};
