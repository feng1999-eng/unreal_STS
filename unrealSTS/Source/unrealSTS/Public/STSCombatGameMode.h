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

/** 战斗关卡 GameMode：生成参战者、初始化牌堆并调用 BeginCombat。 */
UCLASS(Blueprintable, BlueprintType)
class UNREALSTS_API ASTSCombatGameMode : public ASTSGameModeBase
{
	GENERATED_BODY()

public:
	ASTSCombatGameMode();

	UFUNCTION(BlueprintCallable, Category = "STS|Combat")
	ASTSCombatGameState* GetSTSCombatGameState() const;

protected:
	/** 生成玩家/敌人 → InitCombat → BeginCombat。 */
	virtual void StartPlay() override;

	UFUNCTION(BlueprintImplementableEvent, Category = "STS|Combat", meta = (DisplayName = "On Combat Started"))
	void K2_OnCombatStarted();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "STS|Combat")
	TSubclassOf<ASTSPlayerCharacter> PlayerCharacterClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "STS|Combat")
	TSubclassOf<ASTSEnemyCharacter> DefaultEnemyCharacterClass;

	/** 无 Run 数据时使用的角色 DataAsset。 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "STS|Combat")
	TObjectPtr<USTSCharacterData> FallbackCharacterData = nullptr;

	/** 无 PendingEncounter 时使用的遭遇 DataAsset。 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "STS|Combat")
	TObjectPtr<USTSEncounterData> FallbackEncounterData = nullptr;

	/** 为 true 且无 Fallback/Run 数据时，使用 USTSTestContentFactory 内置测试内容。 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "STS|Combat")
	bool bUseBuiltInTestContent = true;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "STS|Combat")
	FVector EnemySpawnOffset = FVector(600.f, 0.f, 0.f);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "STS|Combat")
	float EnemySpawnSpacing = 250.f;

	/** 在 PlayerStart 附近生成玩家并据 Encounter 生成敌人，初始化 ASC 与属性。 */
	void SpawnAndInitializeCombatants(
		ASTSCombatGameState* CombatGameState,
		ASTSPlayerCharacter*& OutPlayer,
		TArray<ASTSEnemyCharacter*>& OutEnemies);

	/**
	 * 解析本场战斗牌组：优先 RunSubsystem.Deck，
	 * 否则 CharacterData.StarterDeck，最后可回退到测试工厂。
	 */
	TArray<FSTSCardInstance> ResolveCombatDeck() const;
};
