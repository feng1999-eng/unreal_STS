// Copyright unrealSTS. All Rights Reserved.

#include "AbilitySystem/STSGameplayAbility_PlayCard.h"
#include "AbilitySystem/STSAbilitySystemComponent.h"
#include "Card/STSCardData.h"
#include "Card/STSEffectExecutor.h"
#include "Combat/STSCombatGameState.h"
#include "Core/STSGameplayTags.h"

USTSGameplayAbility_PlayCard::USTSGameplayAbility_PlayCard()
{
	FGameplayTagContainer Tags;
	Tags.AddTag(STSGameplayTags::Action_PlayCard);
	SetAssetTags(Tags);
}

void USTSGameplayAbility_PlayCard::ActivateAbility(
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

	UWorld* World = ActorInfo && ActorInfo->AvatarActor.IsValid()
		? ActorInfo->AvatarActor->GetWorld()
		: nullptr;
	ASTSCombatGameState* CombatGS = World ? World->GetGameState<ASTSCombatGameState>() : nullptr;
	if (!CombatGS)
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}

	const FSTSCardInstance& CardInstance = CombatGS->GetPendingCardInstance();
	const USTSCardData* CardData = CardInstance.CardData;
	AActor* TargetActor = CombatGS->GetPendingTargetActor();

	USTSAbilitySystemComponent* SourceASC = Cast<USTSAbilitySystemComponent>(ActorInfo->AbilitySystemComponent.Get());
	if (CardData && SourceASC)
	{
		USTSEffectExecutor* Executor = NewObject<USTSEffectExecutor>(this);
		const TArray<FSTSCardEffect> Effects = CardData->GetEffectsForInstance(
			CardInstance.bPermanentUpgrade,
			CardInstance.bCombatUpgrade);
		Executor->ExecuteEffects(Effects, SourceASC, TargetActor, CombatGS);
	}

	K2_ExecuteCardEffects(CardData, TargetActor);
	CombatGS->CompleteCardPlay(CardInstance);

	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}

bool USTSGameplayAbility_PlayCard::CanActivateAbility(
	const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayTagContainer* SourceTags,
	const FGameplayTagContainer* TargetTags,
	FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		return false;
	}

	if (!ActorInfo || !ActorInfo->AvatarActor.IsValid())
	{
		return false;
	}

	UWorld* World = ActorInfo->AvatarActor->GetWorld();
	ASTSCombatGameState* CombatGS = World ? World->GetGameState<ASTSCombatGameState>() : nullptr;
	if (!CombatGS || CombatGS->CombatPhase != ESTSCombatPhase::PlayerTurn)
	{
		return false;
	}

	const USTSCardData* CardData = CombatGS->GetPendingCardInstance().CardData;
	return K2_CanPlayCard(CardData, CombatGS->GetPendingTargetActor());
}

bool USTSGameplayAbility_PlayCard::K2_CanPlayCard_Implementation(const USTSCardData* CardData, AActor* TargetActor) const
{
	return CardData != nullptr;
}
