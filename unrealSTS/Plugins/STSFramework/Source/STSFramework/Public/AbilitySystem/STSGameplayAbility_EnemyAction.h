// Copyright unrealSTS. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/STSGameplayAbility.h"
#include "STSGameplayAbility_EnemyAction.generated.h"

UCLASS(Blueprintable)
class STSFRAMEWORK_API USTSGameplayAbility_EnemyAction : public USTSGameplayAbility
{
	GENERATED_BODY()

public:
	USTSGameplayAbility_EnemyAction();

	virtual void ActivateAbility(
		const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		const FGameplayEventData* TriggerEventData) override;

	UFUNCTION(BlueprintImplementableEvent, Category = "STS|Enemy", meta = (DisplayName = "Execute Enemy Intent"))
	void K2_ExecuteEnemyIntent();
};
