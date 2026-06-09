// Copyright unrealSTS. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "STSGameplayAbility.generated.h"

UCLASS(Abstract, Blueprintable)
class STSFRAMEWORK_API USTSGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	USTSGameplayAbility();

	/** CommitAbility 成功后调用，供 BP 子类接特效/音效。 */
	UFUNCTION(BlueprintImplementableEvent, Category = "STS|Ability", meta = (DisplayName = "On Ability Committed"))
	void K2_OnAbilityCommitted();
};
