// Copyright unrealSTS. All Rights Reserved.

#include "Run/STSRunSubsystem.h"
#include "Character/STSCharacterData.h"
#include "Map/STSActConfigData.h"
#include "Map/STSMapGenerator.h"
#include "Combat/STSEncounterData.h"
#include "Relic/STSRelicData.h"
#include "Card/STSCardData.h"
#include "Kismet/GameplayStatics.h"

void USTSRunSubsystem::NewRun_Implementation()
{
	CurrentAct = 1;
	Gold = 0;
	Deck.Reset();
	OwnedRelics.Reset();
	CurrentMapGraph = FSTSMapGraph();
	CurrentNodeId = NAME_None;
	PendingEncounter = nullptr;

	if (ActiveCharacterData)
	{
		MaxHealth = ActiveCharacterData->StartingMaxHealth;
		CurrentHealth = MaxHealth;

		for (const TObjectPtr<USTSCardData>& StarterCard : ActiveCharacterData->StarterDeck)
		{
			if (!StarterCard)
			{
				continue;
			}

			FSTSCardInstance Instance;
			Instance.CardData = StarterCard;
			Deck.Add(Instance);
		}
	}

	K2_OnNewRunStarted();
}

void USTSRunSubsystem::GenerateMapForAct_Implementation(const USTSActConfigData* ActConfig)
{
	USTSMapGenerator* Generator = NewObject<USTSMapGenerator>(this);
	if (Generator)
	{
		CurrentMapGraph = Generator->GenerateMapForAct(ActConfig);
		if (ActConfig)
		{
			CurrentAct = ActConfig->ActIndex;
		}
	}
}

void USTSRunSubsystem::EnterNode_Implementation(FName NodeId)
{
	CurrentNodeId = NodeId;

	FSTSMapNode Node;
	if (CurrentMapGraph.FindNodeById(NodeId, Node))
	{
		switch (Node.Type)
		{
		case ESTSMapNodeType::Combat:
		case ESTSMapNodeType::Elite:
		case ESTSMapNodeType::Boss:
			PendingEncounter = Node.Encounter;
			if (UWorld* World = GetWorld())
			{
				UGameplayStatics::OpenLevel(World, CombatLevelName);
			}
			break;

		case ESTSMapNodeType::Shop:
		case ESTSMapNodeType::Rest:
		case ESTSMapNodeType::Treasure:
		default:
			break;
		}
	}

	K2_OnNodeEntered(NodeId);
}

void USTSRunSubsystem::AdvanceAct_Implementation()
{
	++CurrentAct;
	CurrentMapGraph = FSTSMapGraph();
	CurrentNodeId = NAME_None;
}

void USTSRunSubsystem::ApplyCombatResult_Implementation(bool bVictory, float RemainingHealth, int32 GoldEarned)
{
	CurrentHealth = RemainingHealth;
	Gold += GoldEarned;
	PendingEncounter = nullptr;
	K2_OnCombatResultApplied(bVictory);
}
