// Copyright unrealSTS. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "STSCardCondition.generated.h"

class USTSCardData;
class ASTSCombatGameState;
class USTSAbilitySystemComponent;

/** Optional complex play rules; default cards need no subclass. */
UCLASS(Abstract, Blueprintable, EditInlineNew, DefaultToInstanced)
class STSFRAMEWORK_API USTSCardCondition : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, Category = "STS|Card")
	bool CanPlayCard(
		const USTSCardData* CardData,
		ASTSCombatGameState* CombatState,
		USTSAbilitySystemComponent* PlayerASC,
		AActor* TargetActor) const;

	virtual bool CanPlayCard_Implementation(
		const USTSCardData* CardData,
		ASTSCombatGameState* CombatState,
		USTSAbilitySystemComponent* PlayerASC,
		AActor* TargetActor) const;
};
