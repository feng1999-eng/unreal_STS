// Copyright unrealSTS. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "Card/STSCardTypes.h"
#include "STSCardData.generated.h"

class USTSCardCondition;

UCLASS(BlueprintType, Const)
class STSFRAMEWORK_API USTSCardData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "STS|Card")
	FText DisplayName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "STS|Card")
	FText Description;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "STS|Card", meta = (Categories = "STS.Card.Type"))
	FGameplayTag CardTypeTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "STS|Card", meta = (Categories = "STS.Card.Rarity"))
	FGameplayTag RarityTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "STS|Card")
	FGameplayTagContainer KeywordTags;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "STS|Card")
	int32 BaseCost = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "STS|Card")
	int32 UpgradedCost = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "STS|Card")
	TArray<FSTSCardEffect> BaseEffects;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "STS|Card")
	TArray<FSTSCardEffect> UpgradedEffects;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "STS|Card")
	TSubclassOf<USTSCardCondition> PlayCondition;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "STS|Card")
	TArray<FSTSCardEffect> GetEffectsForInstance(bool bPermanentUpgrade, bool bCombatUpgrade) const;
};
