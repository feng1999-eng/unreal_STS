// Copyright unrealSTS. All Rights Reserved.

#include "Combat/STSCombatGameState.h"
#include "AbilitySystem/STSAbilitySystemComponent.h"
#include "AbilitySystem/STSAttributeSet.h"
#include "Card/STSCardData.h"
#include "Card/STSCardCondition.h"
#include "Character/STSEnemyCharacter.h"
#include "Character/STSIntentComponent.h"
#include "Character/STSPlayerCharacter.h"
#include "Combat/STSEncounterData.h"
#include "Core/STSGameplayTags.h"
#include "Run/STSRunSubsystem.h"
#include "Engine/GameInstance.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

ASTSCombatGameState::ASTSCombatGameState()
{
}

void ASTSCombatGameState::RegisterCombatants(
	ASTSPlayerCharacter* InPlayerCharacter,
	const TArray<ASTSEnemyCharacter*>& InEnemies)
{
	PlayerCharacter = InPlayerCharacter;
	EnemyCharacters.Reset();
	for (ASTSEnemyCharacter* Enemy : InEnemies)
	{
		EnemyCharacters.Add(Enemy);
	}
}

TArray<ASTSEnemyCharacter*> ASTSCombatGameState::GetEnemyCharacters() const
{
	TArray<ASTSEnemyCharacter*> Result;
	for (ASTSEnemyCharacter* Enemy : EnemyCharacters)
	{
		if (Enemy)
		{
			Result.Add(Enemy);
		}
	}
	return Result;
}

TArray<ASTSEnemyCharacter*> ASTSCombatGameState::GetLivingEnemies() const
{
	TArray<ASTSEnemyCharacter*> Result;
	for (ASTSEnemyCharacter* Enemy : EnemyCharacters)
	{
		if (!Enemy)
		{
			continue;
		}

		if (USTSAbilitySystemComponent* EnemyASC = Cast<USTSAbilitySystemComponent>(Enemy->GetAbilitySystemComponent()))
		{
			if (EnemyASC->GetNumericAttribute(USTSAttributeSet::GetHealthAttribute()) > 0.f)
			{
				Result.Add(Enemy);
			}
		}
	}
	return Result;
}

USTSAbilitySystemComponent* ASTSCombatGameState::GetPlayerASC() const
{
	return PlayerCharacter
		? Cast<USTSAbilitySystemComponent>(PlayerCharacter->GetAbilitySystemComponent())
		: nullptr;
}

void ASTSCombatGameState::InitCombat_Implementation(
	const TArray<FSTSCardInstance>& RunDeck,
	const USTSEncounterData* Encounter)
{
	DrawPile = RunDeck;
	Hand.Reset();
	DiscardPile.Reset();
	ExhaustPile.Reset();
	PlayedPowerCards.Reset();
	PendingCardInstance = FSTSCardInstance();
	PendingEncounter = const_cast<USTSEncounterData*>(Encounter);
	ShuffleDrawPile();
	SetCombatPhase(ESTSCombatPhase::None);
	K2_OnCombatInitialized();
}

void ASTSCombatGameState::BeginCombat()
{
	BroadcastTurnEvent(STSGameplayTags::Event_Combat_Start);
	OnPlayerTurnStart();
}

void ASTSCombatGameState::ShuffleDrawPile()
{
	if (DrawPile.Num() <= 1)
	{
		return;
	}

	for (int32 Index = DrawPile.Num() - 1; Index > 0; --Index)
	{
		const int32 SwapIndex = FMath::RandRange(0, Index);
		DrawPile.Swap(Index, SwapIndex);
	}
}

void ASTSCombatGameState::RefillDrawPileFromDiscard()
{
	if (DiscardPile.Num() == 0)
	{
		return;
	}

	DrawPile.Append(DiscardPile);
	DiscardPile.Reset();
	ShuffleDrawPile();
}

void ASTSCombatGameState::DrawCards_Implementation(int32 Count)
{
	if (Count <= 0)
	{
		return;
	}

	for (int32 Drawn = 0; Drawn < Count; ++Drawn)
	{
		if (DrawPile.Num() == 0)
		{
			RefillDrawPileFromDiscard();
		}

		if (DrawPile.Num() == 0)
		{
			break;
		}

		const int32 TopIndex = DrawPile.Num() - 1;
		Hand.Add(DrawPile[TopIndex]);
		DrawPile.RemoveAt(TopIndex);
	}

	while (Hand.Num() > DefaultHandSize)
	{
		const FSTSCardInstance OverflowCard = Hand[0];
		Hand.RemoveAt(0);
		DiscardPile.Add(OverflowCard);
	}
}

int32 ASTSCombatGameState::FindHandIndexForCard(const USTSCardData* CardData) const
{
	if (!CardData)
	{
		return INDEX_NONE;
	}

	for (int32 Index = 0; Index < Hand.Num(); ++Index)
	{
		if (Hand[Index].CardData == CardData)
		{
			return Index;
		}
	}

	return INDEX_NONE;
}

int32 ASTSCombatGameState::GetCardEnergyCost(const FSTSCardInstance& CardInstance) const
{
	if (!CardInstance.CardData)
	{
		return 0;
	}

	const bool bUseUpgraded = CardInstance.bPermanentUpgrade || CardInstance.bCombatUpgrade;
	return bUseUpgraded ? CardInstance.CardData->UpgradedCost : CardInstance.CardData->BaseCost;
}

bool ASTSCombatGameState::ShouldExhaustCard(const FSTSCardInstance& CardInstance) const
{
	return CardInstance.CardData
		&& CardInstance.CardData->KeywordTags.HasTag(STSGameplayTags::Card_Keyword_Exhaust);
}

bool ASTSCombatGameState::IsPowerCardAlreadyPlayed(const USTSCardData* CardData) const
{
	return CardData
		&& CardData->CardTypeTag == STSGameplayTags::Card_Type_Power
		&& PlayedPowerCards.Contains(CardData->GetPrimaryAssetId());
}

bool ASTSCombatGameState::CanPlayCard(const USTSCardData* CardData, AActor* TargetActor, FText& OutReason) const
{
	if (CombatPhase != ESTSCombatPhase::PlayerTurn)
	{
		OutReason = FText::FromString(TEXT("Not player turn"));
		return false;
	}

	const int32 HandIndex = FindHandIndexForCard(CardData);
	if (HandIndex == INDEX_NONE)
	{
		OutReason = FText::FromString(TEXT("Card not in hand"));
		return false;
	}

	const FSTSCardInstance& CardInstance = Hand[HandIndex];
	if (CardInstance.CardData && CardInstance.CardData->KeywordTags.HasTag(STSGameplayTags::Card_Keyword_Unplayable))
	{
		OutReason = FText::FromString(TEXT("Card is unplayable"));
		return false;
	}

	if (IsPowerCardAlreadyPlayed(CardData))
	{
		OutReason = FText::FromString(TEXT("Power already played"));
		return false;
	}

	if (CardInstance.CardData && CardInstance.CardData->PlayCondition)
	{
		if (USTSCardCondition* Condition = CardInstance.CardData->PlayCondition.GetDefaultObject())
		{
			if (!Condition->CanPlayCard(
				CardInstance.CardData,
				const_cast<ASTSCombatGameState*>(this),
				GetPlayerASC(),
				TargetActor))
			{
				OutReason = FText::FromString(TEXT("Play condition failed"));
				return false;
			}
		}
	}

	if (USTSAbilitySystemComponent* PlayerASC = GetPlayerASC())
	{
		const int32 Cost = GetCardEnergyCost(CardInstance);
		if (PlayerASC->GetNumericAttribute(USTSAttributeSet::GetEnergyAttribute()) < Cost)
		{
			OutReason = FText::FromString(TEXT("Not enough energy"));
			return false;
		}
	}

	return true;
}

bool ASTSCombatGameState::TryPlayCard_Implementation(const USTSCardData* CardData, AActor* TargetActor)
{
	FText Reason;
	if (!CanPlayCard(CardData, TargetActor, Reason))
	{
		return false;
	}

	const int32 HandIndex = FindHandIndexForCard(CardData);
	if (HandIndex == INDEX_NONE)
	{
		return false;
	}

	PendingCardInstance = Hand[HandIndex];
	PendingTargetActor = TargetActor;

	USTSAbilitySystemComponent* PlayerASC = GetPlayerASC();
	if (!PlayerASC || !PlayerASC->TryActivatePlayCardAbility(const_cast<USTSCardData*>(CardData), TargetActor))
	{
		PendingCardInstance = FSTSCardInstance();
		PendingTargetActor = nullptr;
		return false;
	}

	return true;
}

void ASTSCombatGameState::CompleteCardPlay(const FSTSCardInstance& CardInstance)
{
	const int32 HandIndex = FindHandIndexForCard(CardInstance.CardData);
	if (HandIndex == INDEX_NONE)
	{
		return;
	}

	if (USTSAbilitySystemComponent* PlayerASC = GetPlayerASC())
	{
		const int32 Cost = GetCardEnergyCost(CardInstance);
		if (Cost > 0)
		{
			PlayerASC->ApplyModToAttribute(
				USTSAttributeSet::GetEnergyAttribute(),
				EGameplayModOp::Additive,
				-static_cast<float>(Cost));
		}
	}

	FSTSCardInstance PlayedCard = Hand[HandIndex];
	Hand.RemoveAt(HandIndex);

	if (PlayedCard.CardData && PlayedCard.CardData->CardTypeTag == STSGameplayTags::Card_Type_Power)
	{
		PlayedPowerCards.Add(PlayedCard.CardData->GetPrimaryAssetId());
	}

	if (ShouldExhaustCard(PlayedCard))
	{
		ExhaustPile.Add(PlayedCard);
	}
	else
	{
		DiscardPile.Add(PlayedCard);
	}

	AActor* PlayedTarget = PendingTargetActor;
	PendingCardInstance = FSTSCardInstance();
	PendingTargetActor = nullptr;
	BroadcastTurnEvent(STSGameplayTags::Event_Card_Played);
	K2_OnCardPlayed(PlayedCard.CardData, PlayedTarget);
	CheckCombatEnd();
}

void ASTSCombatGameState::ResetPlayerTurnResources()
{
	if (USTSAbilitySystemComponent* PlayerASC = GetPlayerASC())
	{
		PlayerASC->SetNumericAttributeBase(USTSAttributeSet::GetBlockAttribute(), 0.f);
		PlayerASC->SetNumericAttributeBase(
			USTSAttributeSet::GetEnergyAttribute(),
			static_cast<float>(DefaultMaxEnergy));
	}
}

void ASTSCombatGameState::DiscardHandAtTurnEnd()
{
	TArray<FSTSCardInstance> RetainedCards;
	for (const FSTSCardInstance& CardInstance : Hand)
	{
		if (CardInstance.CardData && CardInstance.CardData->KeywordTags.HasTag(STSGameplayTags::Card_Keyword_Retain))
		{
			RetainedCards.Add(CardInstance);
		}
		else
		{
			DiscardPile.Add(CardInstance);
		}
	}

	Hand = RetainedCards;
}

void ASTSCombatGameState::OnPlayerTurnStart_Implementation()
{
	SetCombatPhase(ESTSCombatPhase::PlayerTurn);
	SetPlayerPhaseTags(true);
	ResetPlayerTurnResources();
	DrawCards(DefaultCardsDrawnPerTurn);
	BroadcastTurnEvent(STSGameplayTags::Event_Turn_PlayerStart);
}

void ASTSCombatGameState::EndPlayerTurn_Implementation()
{
	if (CombatPhase != ESTSCombatPhase::PlayerTurn)
	{
		return;
	}

	BroadcastTurnEvent(STSGameplayTags::Event_Turn_PlayerEnd);
	DiscardHandAtTurnEnd();
	OnEnemyTurn();
}

void ASTSCombatGameState::ExecuteEnemyActions()
{
	for (ASTSEnemyCharacter* Enemy : GetLivingEnemies())
	{
		if (!Enemy)
		{
			continue;
		}

		USTSAbilitySystemComponent* EnemyASC = Cast<USTSAbilitySystemComponent>(Enemy->GetAbilitySystemComponent());
		if (!EnemyASC)
		{
			continue;
		}

		EnemyASC->TryActivateAbilityByActionTag(STSGameplayTags::Action_EnemyAct);
	}
}

void ASTSCombatGameState::FinishEnemyTurn()
{
	BroadcastTurnEvent(STSGameplayTags::Event_Turn_EnemyEnd);
	CheckCombatEnd();

	if (CombatPhase == ESTSCombatPhase::Victory || CombatPhase == ESTSCombatPhase::Defeat)
	{
		return;
	}

	OnPlayerTurnStart();
}

void ASTSCombatGameState::OnEnemyTurn_Implementation()
{
	SetCombatPhase(ESTSCombatPhase::EnemyTurn);
	SetPlayerPhaseTags(false);
	BroadcastTurnEvent(STSGameplayTags::Event_Turn_EnemyStart);
	ExecuteEnemyActions();
	FinishEnemyTurn();
}

void ASTSCombatGameState::CheckCombatEnd()
{
	if (CombatPhase == ESTSCombatPhase::Victory || CombatPhase == ESTSCombatPhase::Defeat)
	{
		return;
	}

	if (USTSAbilitySystemComponent* PlayerASC = GetPlayerASC())
	{
		if (PlayerASC->GetNumericAttribute(USTSAttributeSet::GetHealthAttribute()) <= 0.f)
		{
			ApplyCombatDefeat();
			return;
		}
	}

	if (GetLivingEnemies().Num() == 0)
	{
		ApplyCombatVictory();
	}
}

void ASTSCombatGameState::ApplyCombatVictory()
{
	SetCombatPhase(ESTSCombatPhase::Victory);
	BroadcastTurnEvent(STSGameplayTags::Event_Combat_Victory);

	if (UWorld* World = GetWorld())
	{
		if (UGameInstance* GI = World->GetGameInstance())
		{
			if (USTSRunSubsystem* RunSubsystem = GI->GetSubsystem<USTSRunSubsystem>())
			{
				float RemainingHealth = 0.f;
				if (USTSAbilitySystemComponent* PlayerASC = GetPlayerASC())
				{
					RemainingHealth = PlayerASC->GetNumericAttribute(USTSAttributeSet::GetHealthAttribute());
				}

				const int32 GoldReward = PendingEncounter ? PendingEncounter->GoldReward : 0;
				RunSubsystem->ApplyCombatResult(true, RemainingHealth, GoldReward);
			}
		}
	}

	K2_OnCombatEnded(true);
}

void ASTSCombatGameState::ApplyCombatDefeat()
{
	SetCombatPhase(ESTSCombatPhase::Defeat);
	BroadcastTurnEvent(STSGameplayTags::Event_Combat_Defeat);

	if (UWorld* World = GetWorld())
	{
		if (UGameInstance* GI = World->GetGameInstance())
		{
			if (USTSRunSubsystem* RunSubsystem = GI->GetSubsystem<USTSRunSubsystem>())
			{
				RunSubsystem->ApplyCombatResult(false, 0.f, 0);
			}
		}
	}

	K2_OnCombatEnded(false);
}

void ASTSCombatGameState::SetCombatPhase(ESTSCombatPhase NewPhase)
{
	CombatPhase = NewPhase;
	OnCombatPhaseChanged.Broadcast(NewPhase);
	K2_OnPhaseChanged(NewPhase);
}

void ASTSCombatGameState::SetPlayerPhaseTags(bool bPlayerTurn)
{
	USTSAbilitySystemComponent* PlayerASC = GetPlayerASC();
	if (!PlayerASC)
	{
		return;
	}

	PlayerASC->RemoveLooseGameplayTag(STSGameplayTags::Phase_PlayerTurn);
	PlayerASC->RemoveLooseGameplayTag(STSGameplayTags::Phase_EnemyTurn);

	if (bPlayerTurn)
	{
		PlayerASC->AddLooseGameplayTag(STSGameplayTags::Phase_PlayerTurn);
	}
	else
	{
		PlayerASC->AddLooseGameplayTag(STSGameplayTags::Phase_EnemyTurn);
	}
}

void ASTSCombatGameState::BroadcastTurnEvent_Implementation(FGameplayTag EventTag)
{
	if (!EventTag.IsValid())
	{
		return;
	}

	if (USTSAbilitySystemComponent* PlayerASC = GetPlayerASC())
	{
		FGameplayEventData EventData;
		EventData.EventTag = EventTag;
		EventData.Instigator = PlayerCharacter;
		PlayerASC->HandleGameplayEvent(EventTag, &EventData);
	}

	for (ASTSEnemyCharacter* Enemy : GetLivingEnemies())
	{
		if (!Enemy)
		{
			continue;
		}

		if (USTSAbilitySystemComponent* EnemyASC = Cast<USTSAbilitySystemComponent>(Enemy->GetAbilitySystemComponent()))
		{
			FGameplayEventData EventData;
			EventData.EventTag = EventTag;
			EventData.Instigator = Enemy;
			EnemyASC->HandleGameplayEvent(EventTag, &EventData);
		}
	}
}
