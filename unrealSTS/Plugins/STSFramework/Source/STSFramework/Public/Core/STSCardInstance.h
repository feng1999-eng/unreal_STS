// Copyright unrealSTS. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "STSCardInstance.generated.h"

class USTSCardData;

/** Runtime card entry in a run deck (upgrade state lives here, not on DataAsset). */
USTRUCT(BlueprintType)
struct STSFRAMEWORK_API FSTSCardInstance
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "STS")
	TObjectPtr<USTSCardData> CardData = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "STS")
	bool bPermanentUpgrade = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "STS")
	bool bCombatUpgrade = false;
};
