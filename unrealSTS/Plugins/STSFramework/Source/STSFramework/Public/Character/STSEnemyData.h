// Copyright unrealSTS. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Character/STSIntentComponent.h"
#include "STSEnemyData.generated.h"

class USTSAbilitySet;

UCLASS(BlueprintType, Const)
class STSFRAMEWORK_API USTSEnemyData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "STS|Enemy")
	FText DisplayName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "STS|Enemy")
	float MaxHealth = 50.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "STS|Enemy")
	TArray<TObjectPtr<USTSAbilitySet>> AbilitySets;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "STS|Enemy")
	TArray<FSTSEnemyIntent> IntentPattern;
};
