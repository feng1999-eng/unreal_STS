// Copyright unrealSTS. All Rights Reserved.

#include "Card/STSCardCondition.h"
#include "Combat/STSCombatGameState.h"
#include "AbilitySystem/STSAbilitySystemComponent.h"

bool USTSCardCondition::CanPlayCard_Implementation(
	const USTSCardData* CardData,
	ASTSCombatGameState* CombatState,
	USTSAbilitySystemComponent* PlayerASC,
	AActor* TargetActor) const
{
	return true;
}
