// Copyright unrealSTS. All Rights Reserved.

#include "STSCombatDebugLibrary.h"
#include "STSPlayerController.h"
#include "AbilitySystem/STSAbilitySystemComponent.h"
#include "AbilitySystem/STSAttributeSet.h"
#include "Card/STSCardData.h"
#include "Character/STSEnemyCharacter.h"
#include "Combat/STSCombatGameState.h"
#include "Combat/STSCombatTypes.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "HAL/IConsoleManager.h"

/** 从 WorldContext 取当前关卡的 ASTSCombatGameState。 */
static ASTSCombatGameState* GetCombatGameState(const UObject* WorldContextObject)
{
	if (!WorldContextObject)
	{
		return nullptr;
	}

	const UWorld* World = WorldContextObject->GetWorld();
	return World ? World->GetGameState<ASTSCombatGameState>() : nullptr;
}

/** 调试出牌默认目标：第一个仍存活的敌人。 */
static AActor* GetFirstLivingEnemyTarget(ASTSCombatGameState* CombatGS)
{
	if (!CombatGS)
	{
		return nullptr;
	}

	const TArray<ASTSEnemyCharacter*> Enemies = CombatGS->GetLivingEnemies();
	return Enemies.Num() > 0 ? Enemies[0] : nullptr;
}

void USTSCombatDebugLibrary::DebugEndPlayerTurn(const UObject* WorldContextObject)
{
	if (ASTSCombatGameState* CombatGS = GetCombatGameState(WorldContextObject))
	{
		CombatGS->EndPlayerTurn();
	}
}

void USTSCombatDebugLibrary::DebugPlayHandCard(const UObject* WorldContextObject, int32 HandIndex)
{
	ASTSCombatGameState* CombatGS = GetCombatGameState(WorldContextObject);
	if (!CombatGS || !CombatGS->Hand.IsValidIndex(HandIndex))
	{
		return;
	}

	const USTSCardData* CardData = CombatGS->Hand[HandIndex].CardData;
	AActor* Target = GetFirstLivingEnemyTarget(CombatGS);
	CombatGS->TryPlayCard(CardData, Target);
}

void USTSCombatDebugLibrary::DebugPrintCombatState(const UObject* WorldContextObject)
{
	const UWorld* World = WorldContextObject ? WorldContextObject->GetWorld() : nullptr;
	if (!World)
	{
		return;
	}

	ASTSCombatGameState* CombatGS = World->GetGameState<ASTSCombatGameState>();
	if (!CombatGS)
	{
		UE_LOG(LogTemp, Warning, TEXT("[STS] No CombatGameState."));
		return;
	}

	FString Message = FString::Printf(TEXT("Phase=%d Draw=%d Hand=%d Discard=%d"),
		static_cast<int32>(CombatGS->CombatPhase),
		CombatGS->DrawPile.Num(),
		CombatGS->Hand.Num(),
		CombatGS->DiscardPile.Num());

	if (USTSAbilitySystemComponent* PlayerASC = CombatGS->GetPlayerASC())
	{
		Message += FString::Printf(TEXT(" | HP=%.0f Block=%.0f Energy=%.0f"),
			PlayerASC->GetNumericAttribute(USTSAttributeSet::GetHealthAttribute()),
			PlayerASC->GetNumericAttribute(USTSAttributeSet::GetBlockAttribute()),
			PlayerASC->GetNumericAttribute(USTSAttributeSet::GetEnergyAttribute()));
	}

	for (int32 Index = 0; Index < CombatGS->Hand.Num(); ++Index)
	{
		const FText Name = CombatGS->Hand[Index].CardData
			? CombatGS->Hand[Index].CardData->DisplayName
			: FText::FromString(TEXT("?"));
		Message += FString::Printf(TEXT("\n  [%d] %s"), Index, *Name.ToString());
	}

	for (ASTSEnemyCharacter* Enemy : CombatGS->GetLivingEnemies())
	{
		if (!Enemy)
		{
			continue;
		}

		if (USTSAbilitySystemComponent* EnemyASC = Cast<USTSAbilitySystemComponent>(Enemy->GetAbilitySystemComponent()))
		{
			Message += FString::Printf(TEXT("\nEnemy HP=%.0f Block=%.0f"),
				EnemyASC->GetNumericAttribute(USTSAttributeSet::GetHealthAttribute()),
				EnemyASC->GetNumericAttribute(USTSAttributeSet::GetBlockAttribute()));
		}
	}

	UE_LOG(LogTemp, Log, TEXT("[STS] %s"), *Message);
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 4.f, FColor::Cyan, Message);
	}
}

static void STSConsoleEndTurn(const TArray<FString>& Args)
{
	if (GEngine && GEngine->GameViewport)
	{
		if (UWorld* World = GEngine->GameViewport->GetWorld())
		{
			USTSCombatDebugLibrary::DebugEndPlayerTurn(World);
		}
	}
}

static void STSConsolePlayCard(const TArray<FString>& Args)
{
	int32 HandIndex = 0;
	if (Args.Num() > 0)
	{
		HandIndex = FCString::Atoi(*Args[0]);
	}

	if (GEngine && GEngine->GameViewport)
	{
		if (UWorld* World = GEngine->GameViewport->GetWorld())
		{
			USTSCombatDebugLibrary::DebugPlayHandCard(World, HandIndex);
		}
	}
}

static void STSConsoleDebugState(const TArray<FString>& Args)
{
	if (GEngine && GEngine->GameViewport)
	{
		if (UWorld* World = GEngine->GameViewport->GetWorld())
		{
			USTSCombatDebugLibrary::DebugPrintCombatState(World);
		}
	}
}

void USTSCombatDebugLibrary::RegisterConsoleCommands()
{
	static bool bRegistered = false;
	if (bRegistered)
	{
		return;
	}

	bRegistered = true;
	IConsoleManager::Get().RegisterConsoleCommand(
		TEXT("sts.EndTurn"),
		TEXT("End the current player turn."),
		FConsoleCommandWithArgsDelegate::CreateStatic(&STSConsoleEndTurn),
		ECVF_Default);

	IConsoleManager::Get().RegisterConsoleCommand(
		TEXT("sts.PlayCard"),
		TEXT("Play a card from hand by index. Usage: sts.PlayCard 0"),
		FConsoleCommandWithArgsDelegate::CreateStatic(&STSConsolePlayCard),
		ECVF_Default);

	IConsoleManager::Get().RegisterConsoleCommand(
		TEXT("sts.DebugCombat"),
		TEXT("Print combat phase, piles, HP, and hand to log/screen."),
		FConsoleCommandWithArgsDelegate::CreateStatic(&STSConsoleDebugState),
		ECVF_Default);
}
