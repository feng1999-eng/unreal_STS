// Copyright unrealSTS. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "Card/STSCardTypes.h"
#include "STSRelicData.generated.h"

UCLASS(BlueprintType, Const)
class STSFRAMEWORK_API USTSRelicData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "STS|Relic")
	FText DisplayName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "STS|Relic")
	FText Description;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "STS|Relic", meta = (Categories = "STS.Relic.Trigger"))
	FGameplayTag TriggerTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "STS|Relic", meta = (Categories = "STS.Card"))
	FGameplayTagContainer FilterTags;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "STS|Relic")
	TArray<FSTSCardEffect> Effects;
};
