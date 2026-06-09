// Copyright unrealSTS. All Rights Reserved.

#include "STSCombatGameMode.h"
#include "Run/STSGameInstance.h"
#include "Run/STSRunSubsystem.h"
#include "Combat/STSCombatGameState.h"
#include "Combat/STSEncounterData.h"
#include "Character/STSPlayerCharacter.h"
#include "Character/STSEnemyCharacter.h"
#include "Character/STSCharacterData.h"
#include "Card/STSCardData.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h"

ASTSCombatGameMode::ASTSCombatGameMode()
{
	GameStateClass = ASTSCombatGameState::StaticClass();
}

ASTSCombatGameState* ASTSCombatGameMode::GetSTSCombatGameState() const
{
	return GetGameState<ASTSCombatGameState>();
}

TArray<FSTSCardInstance> ASTSCombatGameMode::ResolveCombatDeck() const
{
	if (const USTSGameInstance* GameInstance = Cast<USTSGameInstance>(GetGameInstance()))
	{
		if (const USTSRunSubsystem* RunSubsystem = GameInstance->GetSTSRunSubsystem())
		{
			if (RunSubsystem->Deck.Num() > 0)
			{
				return RunSubsystem->Deck;
			}
		}
	}

	TArray<FSTSCardInstance> StarterDeck;
	const USTSCharacterData* CharacterData = FallbackCharacterData;
	if (const USTSGameInstance* GameInstance = Cast<USTSGameInstance>(GetGameInstance()))
	{
		if (const USTSRunSubsystem* RunSubsystem = GameInstance->GetSTSRunSubsystem())
		{
			if (RunSubsystem->ActiveCharacterData)
			{
				CharacterData = RunSubsystem->ActiveCharacterData;
			}
		}
	}

	if (CharacterData)
	{
		for (const TObjectPtr<USTSCardData>& CardData : CharacterData->StarterDeck)
		{
			if (!CardData)
			{
				continue;
			}

			FSTSCardInstance Instance;
			Instance.CardData = CardData;
			StarterDeck.Add(Instance);
		}
	}

	return StarterDeck;
}

void ASTSCombatGameMode::SpawnAndInitializeCombatants(
	ASTSCombatGameState* CombatGameState,
	ASTSPlayerCharacter*& OutPlayer,
	TArray<ASTSEnemyCharacter*>& OutEnemies)
{
	OutPlayer = nullptr;
	OutEnemies.Reset();

	UWorld* World = GetWorld();
	if (!World)
	{
		return;
	}

	AActor* StartSpot = nullptr;
	for (TActorIterator<APlayerStart> It(World); It; ++It)
	{
		StartSpot = *It;
		break;
	}

	const FVector SpawnLocation = StartSpot ? StartSpot->GetActorLocation() : FVector::ZeroVector;
	const FRotator SpawnRotation = StartSpot ? StartSpot->GetActorRotation() : FRotator::ZeroRotator;

	TSubclassOf<ASTSPlayerCharacter> PawnClass = PlayerCharacterClass;
	if (!PawnClass)
	{
		PawnClass = ASTSPlayerCharacter::StaticClass();
	}

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	OutPlayer = World->SpawnActor<ASTSPlayerCharacter>(PawnClass, SpawnLocation, SpawnRotation, SpawnParams);
	if (!OutPlayer)
	{
		return;
	}

	if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0))
	{
		PlayerController->Possess(OutPlayer);
	}

	OutPlayer->InitializeAbilitySystem();

	const USTSCharacterData* CharacterData = FallbackCharacterData;
	USTSRunSubsystem* RunSubsystem = nullptr;
	if (USTSGameInstance* GameInstance = Cast<USTSGameInstance>(GetGameInstance()))
	{
		RunSubsystem = GameInstance->GetSTSRunSubsystem();
		if (RunSubsystem && RunSubsystem->ActiveCharacterData)
		{
			CharacterData = RunSubsystem->ActiveCharacterData;
		}
	}

	if (CharacterData)
	{
		OutPlayer->InitializeFromCharacterData(CharacterData);
	}
	else
	{
		OutPlayer->GrantDefaultCombatAbilities();
		OutPlayer->SetCombatAttributes(80.f, 80.f);
	}

	if (RunSubsystem && RunSubsystem->MaxHealth > 0.f)
	{
		const float CurrentHealth = RunSubsystem->CurrentHealth > 0.f
			? RunSubsystem->CurrentHealth
			: RunSubsystem->MaxHealth;
		OutPlayer->SetCombatAttributes(RunSubsystem->MaxHealth, CurrentHealth);
	}

	const USTSEncounterData* Encounter = FallbackEncounterData;
	if (RunSubsystem && RunSubsystem->PendingEncounter)
	{
		Encounter = RunSubsystem->PendingEncounter;
	}

	if (!Encounter)
	{
		return;
	}

	TSubclassOf<ASTSEnemyCharacter> EnemyClass = DefaultEnemyCharacterClass;
	if (!EnemyClass)
	{
		EnemyClass = ASTSEnemyCharacter::StaticClass();
	}

	int32 SpawnIndex = 0;
	for (const FSTSEncounterSpawnEntry& SpawnEntry : Encounter->SpawnEntries)
	{
		const TSubclassOf<AActor> EntryClass = SpawnEntry.EnemyClass
			? SpawnEntry.EnemyClass
			: EnemyClass;

		for (int32 Count = 0; Count < SpawnEntry.Count; ++Count)
		{
			const FVector EnemyLocation = SpawnLocation
				+ EnemySpawnOffset
				+ FVector(0.f, SpawnIndex * EnemySpawnSpacing, 0.f);
			const FRotator EnemyRotation = (SpawnLocation - EnemyLocation).Rotation();

			FActorSpawnParameters EnemySpawnParams;
			EnemySpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

			ASTSEnemyCharacter* Enemy = World->SpawnActor<ASTSEnemyCharacter>(
				EntryClass,
				EnemyLocation,
				EnemyRotation,
				EnemySpawnParams);

			if (!Enemy)
			{
				continue;
			}

			Enemy->InitializeAbilitySystem();
			if (SpawnEntry.EnemyData)
			{
				Enemy->InitializeFromEnemyData(SpawnEntry.EnemyData);
			}
			else
			{
				Enemy->GrantDefaultCombatAbilities();
				Enemy->SetCombatAttributes(50.f, 50.f);
			}

			OutEnemies.Add(Enemy);
			++SpawnIndex;
		}
	}
}

void ASTSCombatGameMode::StartPlay()
{
	Super::StartPlay();

	ASTSCombatGameState* CombatGameState = GetSTSCombatGameState();
	if (!CombatGameState)
	{
		K2_OnCombatStarted();
		return;
	}

	ASTSPlayerCharacter* Player = nullptr;
	TArray<ASTSEnemyCharacter*> Enemies;
	SpawnAndInitializeCombatants(CombatGameState, Player, Enemies);

	if (Player)
	{
		CombatGameState->RegisterCombatants(Player, Enemies);
	}

	const TArray<FSTSCardInstance> CombatDeck = ResolveCombatDeck();

	USTSEncounterData* Encounter = nullptr;
	if (USTSGameInstance* GameInstance = Cast<USTSGameInstance>(GetGameInstance()))
	{
		if (USTSRunSubsystem* RunSubsystem = GameInstance->GetSTSRunSubsystem())
		{
			Encounter = RunSubsystem->PendingEncounter;
		}
	}
	if (!Encounter)
	{
		Encounter = FallbackEncounterData;
	}

	CombatGameState->InitCombat(CombatDeck, Encounter);
	CombatGameState->BeginCombat();
	K2_OnCombatStarted();
}
