// Copyright unrealSTS. All Rights Reserved.

#include "AbilitySystem/STSAbilitySet.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffect.h"

void USTSAbilitySet::GiveToAbilitySystem(UAbilitySystemComponent* ASC, FSTSGrantedAbilitySetHandles* OutHandles) const
{
	if (!ASC)
	{
		return;
	}

	for (const FSTSAbilitySet_GameplayAbility& AbilityToGrant : GrantedAbilities)
	{
		if (!AbilityToGrant.Ability)
		{
			continue;
		}

		FGameplayAbilitySpec AbilitySpec(AbilityToGrant.Ability, AbilityToGrant.AbilityLevel);
		if (AbilityToGrant.ActionTag.IsValid())
		{
			AbilitySpec.GetDynamicSpecSourceTags().AddTag(AbilityToGrant.ActionTag);
		}

		const FGameplayAbilitySpecHandle Handle = ASC->GiveAbility(AbilitySpec);
		if (OutHandles && Handle.IsValid())
		{
			OutHandles->AbilitySpecHandles.Add(Handle);
		}
	}

	for (const FSTSAbilitySet_GameplayEffect& EffectToGrant : GrantedEffects)
	{
		if (!EffectToGrant.Effect)
		{
			continue;
		}

		const FGameplayEffectContextHandle Context = ASC->MakeEffectContext();
		const FGameplayEffectSpecHandle SpecHandle = ASC->MakeOutgoingSpec(
			EffectToGrant.Effect,
			EffectToGrant.EffectLevel,
			Context);

		if (!SpecHandle.IsValid())
		{
			continue;
		}

		const FActiveGameplayEffectHandle ActiveHandle = ASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
		if (OutHandles && ActiveHandle.IsValid())
		{
			OutHandles->GameplayEffectHandles.Add(ActiveHandle);
		}
	}
}

void USTSAbilitySet::RemoveFromAbilitySystem(UAbilitySystemComponent* ASC, const FSTSGrantedAbilitySetHandles& Handles) const
{
	if (!ASC)
	{
		return;
	}

	for (const FGameplayAbilitySpecHandle& Handle : Handles.AbilitySpecHandles)
	{
		if (Handle.IsValid())
		{
			ASC->ClearAbility(Handle);
		}
	}

	for (const FActiveGameplayEffectHandle& Handle : Handles.GameplayEffectHandles)
	{
		if (Handle.IsValid())
		{
			ASC->RemoveActiveGameplayEffect(Handle);
		}
	}
}
