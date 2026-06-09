// Copyright unrealSTS. All Rights Reserved.

#include "STSMainMenuGameMode.h"

ASTSMainMenuGameMode::ASTSMainMenuGameMode()
{
}

void ASTSMainMenuGameMode::StartPlay()
{
	Super::StartPlay();
	K2_OnMainMenuStarted();
}
