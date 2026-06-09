// Copyright unrealSTS. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/STSGameplayAbility.h"
#include "STSGameplayAbility_StatusTurnHandler.generated.h"

UCLASS(Blueprintable)
class STSFRAMEWORK_API USTSGameplayAbility_StatusTurnHandler : public USTSGameplayAbility
{
	GENERATED_BODY()

public:
	USTSGameplayAbility_StatusTurnHandler();

	virtual void ActivateAbility(
		const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		const FGameplayEventData* TriggerEventData) override;

	UFUNCTION(BlueprintImplementableEvent, Category = "STS|Status", meta = (DisplayName = "On Turn Event"))
	void K2_OnTurnEvent(FGameplayTag EventTag);
};
