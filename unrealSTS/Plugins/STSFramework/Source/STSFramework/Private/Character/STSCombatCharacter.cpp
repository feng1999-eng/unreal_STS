// Copyright unrealSTS. All Rights Reserved.

#include "Character/STSCombatCharacter.h"
#include "AbilitySystem/STSAbilitySystemComponent.h"
#include "AbilitySystem/STSAttributeSet.h"
#include "AbilitySystem/STSAbilitySet.h"
#include "AbilitySystem/STSGameplayAbility_EnemyAction.h"
#include "AbilitySystem/STSGameplayAbility_PlayCard.h"

ASTSCombatCharacter::ASTSCombatCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	AbilitySystemComponent = CreateDefaultSubobject<USTSAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
}

UAbilitySystemComponent* ASTSCombatCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ASTSCombatCharacter::InitializeAbilitySystem_Implementation()
{
	if (!AbilitySystemComponent)
	{
		return;
	}

	if (!AttributeSet)
	{
		AttributeSet = NewObject<USTSAttributeSet>(this);
		AbilitySystemComponent->AddAttributeSetSubobject(AttributeSet.Get());
	}

	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	K2_OnAbilitySystemInitialized();
}

void ASTSCombatCharacter::GrantAbilitySets_Implementation(const TArray<USTSAbilitySet*>& AbilitySets)
{
	if (!AbilitySystemComponent)
	{
		return;
	}

	for (USTSAbilitySet* AbilitySetAsset : AbilitySets)
	{
		if (AbilitySetAsset)
		{
			AbilitySetAsset->GiveToAbilitySystem(AbilitySystemComponent, &GrantedAbilitySetHandles);
		}
	}
}

void ASTSCombatCharacter::SetCombatAttributes(float InMaxHealth, float InCurrentHealth)
{
	if (!AbilitySystemComponent || !AttributeSet)
	{
		return;
	}

	AbilitySystemComponent->SetNumericAttributeBase(USTSAttributeSet::GetMaxHealthAttribute(), InMaxHealth);
	AbilitySystemComponent->SetNumericAttributeBase(
		USTSAttributeSet::GetHealthAttribute(),
		FMath::Clamp(InCurrentHealth, 0.f, InMaxHealth));
}

void ASTSCombatCharacter::GrantDefaultCombatAbilities()
{
	if (!AbilitySystemComponent)
	{
		return;
	}

	AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(
		USTSGameplayAbility_PlayCard::StaticClass(),
		1,
		INDEX_NONE,
		this));
}
