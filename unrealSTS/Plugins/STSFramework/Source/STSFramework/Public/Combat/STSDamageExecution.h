// Copyright unrealSTS. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "STSDamageExecution.generated.h"

UCLASS()
class STSFRAMEWORK_API USTSDamageExecution : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

public:
	USTSDamageExecution();

	virtual void Execute_Implementation(
		const FGameplayEffectCustomExecutionParameters& ExecutionParams,
		FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
};
