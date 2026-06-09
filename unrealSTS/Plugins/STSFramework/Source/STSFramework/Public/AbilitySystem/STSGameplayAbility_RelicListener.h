// Copyright unrealSTS. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/STSGameplayAbility.h"
#include "STSGameplayAbility_RelicListener.generated.h"

UCLASS(Blueprintable)
class STSFRAMEWORK_API USTSGameplayAbility_RelicListener : public USTSGameplayAbility
{
	GENERATED_BODY()

public:
	USTSGameplayAbility_RelicListener();

	virtual void ActivateAbility(
		const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		const FGameplayEventData* TriggerEventData) override;

	UFUNCTION(BlueprintImplementableEvent, Category = "STS|Relic", meta = (DisplayName = "On Relic Event"))
	void K2_OnRelicGameplayEvent(FGameplayTag EventTag);
};
