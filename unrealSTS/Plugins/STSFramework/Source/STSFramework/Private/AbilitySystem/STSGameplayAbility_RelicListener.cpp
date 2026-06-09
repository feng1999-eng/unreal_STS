// Copyright unrealSTS. All Rights Reserved.

#include "AbilitySystem/STSGameplayAbility_RelicListener.h"
#include "Core/STSGameplayTags.h"

USTSGameplayAbility_RelicListener::USTSGameplayAbility_RelicListener()
{
	FGameplayTagContainer Tags;
	Tags.AddTag(STSGameplayTags::Action_RelicListen);
	SetAssetTags(Tags);
}

void USTSGameplayAbility_RelicListener::ActivateAbility(
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
		K2_OnRelicGameplayEvent(TriggerEventData->EventTag);
	}

	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}
