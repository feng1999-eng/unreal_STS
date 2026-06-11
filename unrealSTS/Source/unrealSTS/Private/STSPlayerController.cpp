// Copyright unrealSTS. All Rights Reserved.

#include "STSPlayerController.h"
#include "STSCombatDebugLibrary.h"
#include "InputCoreTypes.h"

ASTSPlayerController::ASTSPlayerController()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
}

// 注册控制台命令并显示调试说明
void ASTSPlayerController::BeginPlay()
{
	Super::BeginPlay();

	USTSCombatDebugLibrary::RegisterConsoleCommands();
	ShowDebugHelp();
	USTSCombatDebugLibrary::DebugPrintCombatState(this);
	K2_OnPlayerControllerReady();
}

void ASTSPlayerController::ShowDebugHelp() const
{
	const FString Help = TEXT(
		"[STS Phase1/2 Debug]\n"
		"Keys 1-5: play hand card index 0-4\n"
		"E: end player turn\n"
		"P: print combat state\n"
		"Console: sts.PlayCard 0 | sts.EndTurn | sts.DebugCombat");

	UE_LOG(LogTemp, Log, TEXT("%s"), *Help);
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 8.f, FColor::Green, Help);
	}
}

// 1–5 出牌，E 结束回合，P 刷新状态
void ASTSPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (!InputComponent)
	{
		return;
	}

	InputComponent->BindKey(EKeys::E, IE_Pressed, this, &ASTSPlayerController::HandleDebugEndTurn);
	InputComponent->BindKey(EKeys::P, IE_Pressed, this, &ASTSPlayerController::HandleDebugPrintState);
	InputComponent->BindKey(EKeys::One, IE_Pressed, this, &ASTSPlayerController::HandlePlayCardKey0);
	InputComponent->BindKey(EKeys::Two, IE_Pressed, this, &ASTSPlayerController::HandlePlayCardKey1);
	InputComponent->BindKey(EKeys::Three, IE_Pressed, this, &ASTSPlayerController::HandlePlayCardKey2);
	InputComponent->BindKey(EKeys::Four, IE_Pressed, this, &ASTSPlayerController::HandlePlayCardKey3);
	InputComponent->BindKey(EKeys::Five, IE_Pressed, this, &ASTSPlayerController::HandlePlayCardKey4);
}

void ASTSPlayerController::HandleDebugEndTurn()
{
	USTSCombatDebugLibrary::DebugEndPlayerTurn(this);
	USTSCombatDebugLibrary::DebugPrintCombatState(this);
}

void ASTSPlayerController::HandleDebugPrintState()
{
	USTSCombatDebugLibrary::DebugPrintCombatState(this);
}

void ASTSPlayerController::HandleDebugPlayHandCard(int32 HandIndex)
{
	USTSCombatDebugLibrary::DebugPlayHandCard(this, HandIndex);
	USTSCombatDebugLibrary::DebugPrintCombatState(this);
}
