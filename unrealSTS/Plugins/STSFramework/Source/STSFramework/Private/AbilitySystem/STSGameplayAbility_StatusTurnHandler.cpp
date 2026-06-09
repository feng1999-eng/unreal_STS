// Copyright unrealSTS. All Rights Reserved.

#include "AbilitySystem/STSGameplayAbility_StatusTurnHandler.h"
#include "Core/STSGameplayTags.h"

USTSGameplayAbility_StatusTurnHandler::USTSGameplayAbility_StatusTurnHandler()
{
	FGameplayTagContainer Tags;
	Tags.AddTag(STSGameplayTags::Action_StatusTurn);
	SetAssetTags(Tags);
}

void USTSGameplayAbility_StatusTurnHandler::ActivateAbility(
	const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}

	K2_OnAbilityCommitted();

	if (TriggerEventData && TriggerEventData->EventTag.IsValid())
	{
		K2_OnTurnEvent(TriggerEventData->EventTag);
	}

	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}
