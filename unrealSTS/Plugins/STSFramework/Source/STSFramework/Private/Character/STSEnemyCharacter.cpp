// Copyright unrealSTS. All Rights Reserved.

#include "Character/STSEnemyCharacter.h"
#include "Character/STSEnemyData.h"
#include "Character/STSIntentComponent.h"
#include "AbilitySystem/STSAbilitySet.h"
#include "AbilitySystem/STSAbilitySystemComponent.h"
#include "AbilitySystem/STSGameplayAbility_EnemyAction.h"

ASTSEnemyCharacter::ASTSEnemyCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	IntentComponent = CreateDefaultSubobject<USTSIntentComponent>(TEXT("IntentComponent"));
}

void ASTSEnemyCharacter::InitializeFromEnemyData_Implementation(const USTSEnemyData* EnemyData)
{
	if (!EnemyData)
	{
		return;
	}

	TArray<USTSAbilitySet*> AbilitySets;
	for (USTSAbilitySet* Set : EnemyData->AbilitySets)
	{
		AbilitySets.Add(Set);
	}

	if (IntentComponent && EnemyData->IntentPattern.Num() > 0)
	{
		IntentComponent->IntentPattern = EnemyData->IntentPattern;
		IntentComponent->RollNextIntent();
	}

	GrantAbilitySets(AbilitySets);

	if (AbilitySets.Num() == 0)
	{
		if (AbilitySystemComponent)
		{
			AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(
				USTSGameplayAbility_EnemyAction::StaticClass(),
				1,
				INDEX_NONE,
				this));
		}
	}

	SetCombatAttributes(EnemyData->MaxHealth, EnemyData->MaxHealth);
	K2_OnEnemyDataApplied(EnemyData);
}

void ASTSEnemyCharacter::GrantDefaultCombatAbilities()
{
	if (!AbilitySystemComponent)
	{
		return;
	}

	AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(
		USTSGameplayAbility_EnemyAction::StaticClass(),
		1,
		INDEX_NONE,
		this));
}
