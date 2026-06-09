// Copyright unrealSTS. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "STSBuffRegistry.generated.h"

class USTSBuffDefinition;

UCLASS(BlueprintType, Const)
class STSFRAMEWORK_API USTSBuffRegistry : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "STS|Buff")
	TArray<TObjectPtr<USTSBuffDefinition>> BuffDefinitions;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "STS|Buff")
	USTSBuffDefinition* FindBuffDefinition(FGameplayTag BuffTag) const;
};
