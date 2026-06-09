// Copyright unrealSTS. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "STSGameModeBase.h"
#include "Core/STSCardInstance.h"
#include "STSCombatGameMode.generated.h"

class ASTSCombatGameState;
class ASTSPlayerCharacter;
class ASTSEnemyCharacter;
class USTSCharacterData;
class USTSEncounterData;

UCLASS(Blueprintable, BlueprintType)
class UNREALSTS_API ASTSCombatGameMode : public ASTSGameModeBase
{
	GENERATED_BODY()

public:
	ASTSCombatGameMode();

	UFUNCTION(BlueprintCallable, Category = "STS|Combat")
	ASTSCombatGameState* GetSTSCombatGameState() const;

protected:
	virtual void StartPlay() override;

	UFUNCTION(BlueprintImplementableEvent, Category = "STS|Combat", meta = (DisplayName = "On Combat Started"))
	void K2_OnCombatStarted();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "STS|Combat")
	TSubclassOf<ASTSPlayerCharacter> PlayerCharacterClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "STS|Combat")
	TSubclassOf<ASTSEnemyCharacter> DefaultEnemyCharacterClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "STS|Combat")
	TObjectPtr<USTSCharacterData> FallbackCharacterData = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "STS|Combat")
	TObjectPtr<USTSEncounterData> FallbackEncounterData = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "STS|Combat")
	FVector EnemySpawnOffset = FVector(600.f, 0.f, 0.f);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "STS|Combat")
	float EnemySpawnSpacing = 250.f;

	void SpawnAndInitializeCombatants(
		ASTSCombatGameState* CombatGameState,
		ASTSPlayerCharacter*& OutPlayer,
		TArray<ASTSEnemyCharacter*>& OutEnemies);

	TArray<FSTSCardInstance> ResolveCombatDeck() const;
};
