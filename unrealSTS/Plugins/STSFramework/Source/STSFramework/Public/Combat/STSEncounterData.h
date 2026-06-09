// Copyright unrealSTS. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Character/STSEnemyData.h"
#include "STSEncounterData.generated.h"

USTRUCT(BlueprintType)
struct STSFRAMEWORK_API FSTSEncounterSpawnEntry
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "STS|Encounter")
	TSubclassOf<AActor> EnemyClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "STS|Encounter")
	TObjectPtr<USTSEnemyData> EnemyData = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "STS|Encounter")
	int32 Count = 1;
};

UCLASS(BlueprintType, Const)
class STSFRAMEWORK_API USTSEncounterData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "STS|Encounter")
	FText DisplayName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "STS|Encounter")
	TArray<FSTSEncounterSpawnEntry> SpawnEntries;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "STS|Encounter")
	int32 GoldReward = 0;
};
