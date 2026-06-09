// Copyright unrealSTS. All Rights Reserved.

#include "Character/STSIntentComponent.h"

void USTSIntentComponent::RollNextIntent()
{
	if (IntentPattern.Num() == 0)
	{
		CurrentIntent = FSTSEnemyIntent();
		return;
	}

	CurrentIntent = IntentPattern[CurrentPatternIndex];
	CurrentPatternIndex = (CurrentPatternIndex + 1) % IntentPattern.Num();
}
