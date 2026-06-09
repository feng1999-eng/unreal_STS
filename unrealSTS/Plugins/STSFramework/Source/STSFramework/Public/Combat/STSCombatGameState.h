// Copyright unrealSTS. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "GameplayTagContainer.h"
#include "Combat/STSCombatTypes.h"
#include "Core/STSCardInstance.h"
#include "STSCombatGameState.generated.h"

class USTSCardData;
class USTSEncounterData;
class ASTSCombatCharacter;
class ASTSPlayerCharacter;
class ASTSEnemyCharacter;
class USTSAbilitySystemComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSTSCombatPhaseChangedSignature, ESTSCombatPhase, NewPhase);

UCLASS(Blueprintable, BlueprintType)
class STSFRAMEWORK_API ASTSCombatGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	ASTSCombatGameState();

	UPROPERTY(BlueprintAssignable, Category = "STS|Combat")
	FSTSCombatPhaseChangedSignature OnCombatPhaseChanged;

	UPROPERTY(BlueprintReadOnly, Category = "STS|Combat")
	ESTSCombatPhase CombatPhase = ESTSCombatPhase::None;

	UPROPERTY(BlueprintReadOnly, Category = "STS|Combat")
	TArray<FSTSCardInstance> DrawPile;

	UPROPERTY(BlueprintReadOnly, Category = "STS|Combat")
	TArray<FSTSCardInstance> Hand;

	UPROPERTY(BlueprintReadOnly, Category = "STS|Combat")
	TArray<FSTSCardInstance> DiscardPile;

	UPROPERTY(BlueprintReadOnly, Category = "STS|Combat")
	TArray<FSTSCardInstance> ExhaustPile;

	UPROPERTY(BlueprintReadOnly, Category = "STS|Combat")
	TObjectPtr<USTSEncounterData> PendingEncounter = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "STS|Combat")
	int32 DefaultHandSize = 5;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "STS|Combat")
	int32 DefaultMaxEnergy = 3;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "STS|Combat")
	int32 DefaultCardsDrawnPerTurn = 5;

	UFUNCTION(BlueprintCallable, Category = "STS|Combat")
	void RegisterCombatants(ASTSPlayerCharacter* InPlayerCharacter, const TArray<ASTSEnemyCharacter*>& InEnemies);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "STS|Combat")
	ASTSPlayerCharacter* GetPlayerCharacter() const { return PlayerCharacter; }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "STS|Combat")
	TArray<ASTSEnemyCharacter*> GetEnemyCharacters() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "STS|Combat")
	TArray<ASTSEnemyCharacter*> GetLivingEnemies() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "STS|Combat")
	USTSAbilitySystemComponent* GetPlayerASC() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "STS|Combat")
	const FSTSCardInstance& GetPendingCardInstance() const { return PendingCardInstance; }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "STS|Combat")
	AActor* GetPendingTargetActor() const { return PendingTargetActor; }

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "STS|Combat")
	void InitCombat(const TArray<FSTSCardInstance>& RunDeck, const USTSEncounterData* Encounter);

	UFUNCTION(BlueprintCallable, Category = "STS|Combat")
	void BeginCombat();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "STS|Combat")
	bool TryPlayCard(const USTSCardData* CardData, AActor* TargetActor);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "STS|Combat")
	void EndPlayerTurn();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "STS|Combat")
	void OnPlayerTurnStart();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "STS|Combat")
	void OnEnemyTurn();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "STS|Combat")
	void DrawCards(int32 Count);

	UFUNCTION(BlueprintCallable, Category = "STS|Combat")
	void CompleteCardPlay(const FSTSCardInstance& CardInstance);

	UFUNCTION(BlueprintCallable, Category = "STS|Combat")
	void CheckCombatEnd();

	UFUNCTION(BlueprintCallable, Category = "STS|Combat")
	bool CanPlayCard(const USTSCardData* CardData, AActor* TargetActor, FText& OutReason) const;

	UFUNCTION(BlueprintImplementableEvent, Category = "STS|Combat", meta = (DisplayName = "On Combat Initialized"))
	void K2_OnCombatInitialized();

	UFUNCTION(BlueprintImplementableEvent, Category = "STS|Combat", meta = (DisplayName = "On Phase Changed"))
	void K2_OnPhaseChanged(ESTSCombatPhase NewPhase);

	UFUNCTION(BlueprintImplementableEvent, Category = "STS|Combat", meta = (DisplayName = "On Card Played"))
	void K2_OnCardPlayed(const USTSCardData* CardData, AActor* TargetActor);

	UFUNCTION(BlueprintImplementableEvent, Category = "STS|Combat", meta = (DisplayName = "On Combat Ended"))
	void K2_OnCombatEnded(bool bVictory);

protected:
	UPROPERTY(BlueprintReadOnly, Category = "STS|Combat")
	TObjectPtr<ASTSPlayerCharacter> PlayerCharacter = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "STS|Combat")
	TArray<TObjectPtr<ASTSEnemyCharacter>> EnemyCharacters;

	UPROPERTY(BlueprintReadOnly, Category = "STS|Combat")
	FSTSCardInstance PendingCardInstance;

	UPROPERTY(BlueprintReadOnly, Category = "STS|Combat")
	TObjectPtr<AActor> PendingTargetActor = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "STS|Combat")
	TSet<FPrimaryAssetId> PlayedPowerCards;

	virtual void SetCombatPhase(ESTSCombatPhase NewPhase);
	void SetPlayerPhaseTags(bool bPlayerTurn);
	void ShuffleDrawPile();
	void RefillDrawPileFromDiscard();
	void DiscardHandAtTurnEnd();
	void ResetPlayerTurnResources();
	int32 FindHandIndexForCard(const USTSCardData* CardData) const;
	int32 GetCardEnergyCost(const FSTSCardInstance& CardInstance) const;
	bool ShouldExhaustCard(const FSTSCardInstance& CardInstance) const;
	bool IsPowerCardAlreadyPlayed(const USTSCardData* CardData) const;
	void ExecuteEnemyActions();
	void FinishEnemyTurn();
	void ApplyCombatVictory();
	void ApplyCombatDefeat();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "STS|Combat")
	void BroadcastTurnEvent(FGameplayTag EventTag);
};
