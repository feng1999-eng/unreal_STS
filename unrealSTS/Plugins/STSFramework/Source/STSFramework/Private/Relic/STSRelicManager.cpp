// Copyright unrealSTS. All Rights Reserved.

#include "Relic/STSRelicManager.h"
#include "AbilitySystem/STSAbilitySystemComponent.h"

void USTSRelicManager::Initialize(USTSAbilitySystemComponent* InPlayerASC)
{
	PlayerASC = InPlayerASC;
}

void USTSRelicManager::HandleGameplayEvent_Implementation(FGameplayTag EventTag, const FGameplayEventData& Payload)
{
	K2_OnRelicEvent(EventTag);
}
