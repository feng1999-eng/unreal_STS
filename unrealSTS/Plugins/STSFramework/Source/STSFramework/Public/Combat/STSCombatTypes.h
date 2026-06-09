// Copyright unrealSTS. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "STSCombatTypes.generated.h"

UENUM(BlueprintType)
enum class ESTSCombatPhase : uint8
{
	None,
	PlayerTurn,
	EnemyTurn,
	Victory,
	Defeat
};
