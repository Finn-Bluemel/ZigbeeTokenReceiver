#include "TokenSlotComponent.h"
#include "TokenDataSubsystem.h"
#include "Engine/GameInstance.h"
#include "Engine/World.h"

UTokenSlotComponent::UTokenSlotComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UTokenSlotComponent::BeginPlay()
{
    Super::BeginPlay();

    UGameInstance* GI = GetWorld() ? GetWorld()->GetGameInstance() : nullptr;
    if (!GI) return;

    UTokenDataSubsystem* Sub = GI->GetSubsystem<UTokenDataSubsystem>();
    if (!Sub) return;

    Sub->OnTokenReceived.AddDynamic(this, &UTokenSlotComponent::HandleTokenReceived);

    if (bAutoDetectPort)
    {
        Sub->AutoOpenPort(BaudRate);
    }

    if (bStartDummyIfNoDevice && !Sub->IsConnected())
    {
        Sub->StartDummyMode(DummyInterval);
    }
}

void UTokenSlotComponent::HandleTokenReceived(const FTokenData& Data)
{
    if (FilterTokenId != -1 && Data.TokenId != FilterTokenId) return;
    OnTokenData.Broadcast(Data.TokenId, Data.Slot0, Data.Slot1, Data.Slot2, Data.Slot3, Data.BatteryMv);
}
