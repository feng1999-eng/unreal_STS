// Copyright unrealSTS. All Rights Reserved.

#include "STSMapGameMode.h"

ASTSMapGameMode::ASTSMapGameMode()
{
}

void ASTSMapGameMode::StartPlay()
{
	Super::StartPlay();
	K2_OnMapStarted();
}
