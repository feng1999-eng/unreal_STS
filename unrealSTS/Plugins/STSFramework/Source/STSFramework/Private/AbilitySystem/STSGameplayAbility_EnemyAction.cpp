// Copyright unrealSTS. All Rights Reserved.

#include "AbilitySystem/STSGameplayAbility_EnemyAction.h"
#include "AbilitySystem/STSAbilitySystemComponent.h"
#include "Card/STSEffectExecutor.h"
#include "Character/STSEnemyCharacter.h"
#include "Character/STSIntentComponent.h"
#include "Character/STSPlayerCharacter.h"
#include "Combat/STSCombatGameState.h"
#include "Core/STSGameplayTags.h"

USTSGameplayAbility_EnemyAction::USTSGameplayAbility_EnemyAction()
{
	FGameplayTagContainer Tags;
	Tags.AddTag(STSGameplayTags::Action_EnemyAct);
	SetAssetTags(Tags);
}

void USTSGameplayAbility_EnemyAction::ActivateAbility(
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

	ASTSEnemyCharacter* Enemy = ActorInfo ? Cast<ASTSEnemyCharacter>(ActorInfo->AvatarActor.Get()) : nullptr;
	UWorld* World = Enemy ? Enemy->GetWorld() : nullptr;
	ASTSCombatGameState* CombatGS = World ? World->GetGameState<ASTSCombatGameState>() : nullptr;
	USTSAbilitySystemComponent* EnemyASC = ActorInfo
		? Cast<USTSAbilitySystemComponent>(ActorInfo->AbilitySystemComponent.Get())
		: nullptr;

	if (Enemy && EnemyASC && CombatGS)
	{
		ASTSPlayerCharacter* Player = CombatGS->GetPlayerCharacter();
		USTSAbilitySystemComponent* PlayerASC = CombatGS->GetPlayerASC();

		if (USTSIntentComponent* IntentComponent = Enemy->GetIntentComponent())
		{
			USTSEffectExecutor* Executor = NewObject<USTSEffectExecutor>(this);
			Executor->ExecuteEffects(
				IntentComponent->CurrentIntent.Effects,
				EnemyASC,
				Player,
				CombatGS);

			IntentComponent->RollNextIntent();
		}
	}

	K2_ExecuteEnemyIntent();

	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}
