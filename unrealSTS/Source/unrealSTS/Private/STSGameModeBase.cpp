// Copyright unrealSTS. All Rights Reserved.

#include "STSGameModeBase.h"
#include "STSPlayerController.h"

ASTSGameModeBase::ASTSGameModeBase()
{
	PlayerControllerClass = ASTSPlayerController::StaticClass();
}

void ASTSGameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
	K2_OnGameInitialized();
}
