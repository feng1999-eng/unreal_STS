// Copyright unrealSTS. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Combat/STSEncounterData.h"
#include "STSActConfigData.generated.h"

UCLASS(BlueprintType, Const)
class STSFRAMEWORK_API USTSActConfigData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "STS|Map")
	int32 ActIndex = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "STS|Map")
	int32 MapLayerCount = 8;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "STS|Map")
	TArray<TObjectPtr<USTSEncounterData>> NormalEncounterPool;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "STS|Map")
	TArray<TObjectPtr<USTSEncounterData>> EliteEncounterPool;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "STS|Map")
	TObjectPtr<USTSEncounterData> BossEncounter = nullptr;
};
