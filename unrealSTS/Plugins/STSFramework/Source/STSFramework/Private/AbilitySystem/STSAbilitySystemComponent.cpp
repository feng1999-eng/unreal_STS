// Copyright unrealSTS. All Rights Reserved.

#include "AbilitySystem/STSAbilitySystemComponent.h"
#include "AbilitySystem/STSGameplayAbility_PlayCard.h"
#include "Card/STSCardData.h"
#include "Core/STSGameplayTags.h"

bool USTSAbilitySystemComponent::TryActivateAbilityByActionTag(const FGameplayTag& ActionTag)
{
	if (!ActionTag.IsValid())
	{
		return false;
	}

	FGameplayTagContainer TagContainer;
	TagContainer.AddTag(ActionTag);
	TArray<FGameplayAbilitySpec*> MatchingSpecs;
	GetActivatableGameplayAbilitySpecsByAllMatchingTags(TagContainer, MatchingSpecs);

	for (FGameplayAbilitySpec* Spec : MatchingSpecs)
	{
		if (Spec && TryActivateAbility(Spec->Handle))
		{
			return true;
		}
	}

	return false;
}

bool USTSAbilitySystemComponent::TryActivatePlayCardAbility(USTSCardData* CardData, AActor* TargetActor)
{
	FGameplayTagContainer TagContainer;
	TagContainer.AddTag(STSGameplayTags::Action_PlayCard);
	TArray<FGameplayAbilitySpec*> MatchingSpecs;
	GetActivatableGameplayAbilitySpecsByAllMatchingTags(TagContainer, MatchingSpecs);

	for (FGameplayAbilitySpec* Spec : MatchingSpecs)
	{
		if (!Spec)
		{
			continue;
		}

		if (TryActivateAbility(Spec->Handle))
		{
			return true;
		}
	}

	return false;
}
