// Copyright unrealSTS. All Rights Reserved.

#include "Character/STSPlayerCharacter.h"
#include "Character/STSCharacterData.h"
#include "AbilitySystem/STSAbilitySet.h"

ASTSPlayerCharacter::ASTSPlayerCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void ASTSPlayerCharacter::InitializeFromCharacterData_Implementation(const USTSCharacterData* CharacterData)
{
	if (!CharacterData)
	{
		return;
	}

	TArray<USTSAbilitySet*> AbilitySets;
	for (USTSAbilitySet* Set : CharacterData->AbilitySets)
	{
		AbilitySets.Add(Set);
	}

	GrantAbilitySets(AbilitySets);

	if (AbilitySets.Num() == 0)
	{
		GrantDefaultCombatAbilities();
	}

	SetCombatAttributes(CharacterData->StartingMaxHealth, CharacterData->StartingMaxHealth);
	K2_OnCharacterDataApplied(CharacterData);
}
