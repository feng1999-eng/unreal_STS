// Copyright unrealSTS. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Core/STSCardInstance.h"
#include "STSCharacterData.generated.h"

class USTSAbilitySet;
class USTSCardData;

UCLASS(BlueprintType, Const)
class STSFRAMEWORK_API USTSCharacterData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "STS|Character")
	FText DisplayName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "STS|Character")
	float StartingMaxHealth = 80.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "STS|Character")
	TArray<TObjectPtr<USTSAbilitySet>> AbilitySets;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "STS|Character")
	TArray<TObjectPtr<USTSCardData>> StarterDeck;
};
