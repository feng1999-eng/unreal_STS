// Copyright unrealSTS. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Card/STSCardTypes.h"
#include "STSEffectExecutor.generated.h"

class USTSAbilitySystemComponent;
class ASTSCombatGameState;

UCLASS(Blueprintable, BlueprintType)
class STSFRAMEWORK_API USTSEffectExecutor : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "STS|Card")
	void ExecuteEffects(
		const TArray<FSTSCardEffect>& Effects,
		USTSAbilitySystemComponent* SourceASC,
		AActor* TargetActor,
		ASTSCombatGameState* CombatGameState);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "STS|Card")
	void ExecuteEffect(
		const FSTSCardEffect& Effect,
		USTSAbilitySystemComponent* SourceASC,
		USTSAbilitySystemComponent* TargetASC);
};
