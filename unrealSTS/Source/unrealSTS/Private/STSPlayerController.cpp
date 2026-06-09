// Copyright unrealSTS. All Rights Reserved.

#include "STSPlayerController.h"

ASTSPlayerController::ASTSPlayerController()
{
}

void ASTSPlayerController::BeginPlay()
{
	Super::BeginPlay();
	K2_OnPlayerControllerReady();
}
