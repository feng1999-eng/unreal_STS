// Copyright unrealSTS. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Core/STSCardInstance.h"
#include "Run/STSMapTypes.h"
#include "STSRunSubsystem.generated.h"

class USTSRelicData;
class USTSEncounterData;
class USTSActConfigData;
class USTSCharacterData;

UCLASS(Blueprintable)
class STSFRAMEWORK_API USTSRunSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, Category = "STS|Run")
	int32 CurrentAct = 1;

	UPROPERTY(BlueprintReadOnly, Category = "STS|Run")
	int32 Gold = 0;

	UPROPERTY(BlueprintReadOnly, Category = "STS|Run")
	float CurrentHealth = 0.f;

	UPROPERTY(BlueprintReadOnly, Category = "STS|Run")
	float MaxHealth = 0.f;

	UPROPERTY(BlueprintReadOnly, Category = "STS|Run")
	TArray<FSTSCardInstance> Deck;

	UPROPERTY(BlueprintReadOnly, Category = "STS|Run")
	TArray<TObjectPtr<USTSRelicData>> OwnedRelics;

	UPROPERTY(BlueprintReadOnly, Category = "STS|Run")
	FSTSMapGraph CurrentMapGraph;

	UPROPERTY(BlueprintReadOnly, Category = "STS|Run")
	FName CurrentNodeId;

	UPROPERTY(BlueprintReadOnly, Category = "STS|Run")
	TObjectPtr<USTSEncounterData> PendingEncounter = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "STS|Run")
	TObjectPtr<USTSCharacterData> ActiveCharacterData = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "STS|Run")
	FName CombatLevelName = FName(TEXT("L_Combat"));

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "STS|Run")
	void NewRun();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "STS|Run")
	void GenerateMapForAct(const USTSActConfigData* ActConfig);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "STS|Run")
	void EnterNode(FName NodeId);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "STS|Run")
	void AdvanceAct();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "STS|Run")
	void ApplyCombatResult(bool bVictory, float RemainingHealth, int32 GoldEarned);

	UFUNCTION(BlueprintImplementableEvent, Category = "STS|Run", meta = (DisplayName = "On New Run Started"))
	void K2_OnNewRunStarted();

	UFUNCTION(BlueprintImplementableEvent, Category = "STS|Run", meta = (DisplayName = "On Node Entered"))
	void K2_OnNodeEntered(FName NodeId);

	UFUNCTION(BlueprintImplementableEvent, Category = "STS|Run", meta = (DisplayName = "On Combat Result Applied"))
	void K2_OnCombatResultApplied(bool bVictory);
};
