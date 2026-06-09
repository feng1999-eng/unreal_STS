// Copyright unrealSTS. All Rights Reserved.

#include "Card/STSCardData.h"

TArray<FSTSCardEffect> USTSCardData::GetEffectsForInstance(bool bPermanentUpgrade, bool bCombatUpgrade) const
{
	const bool bUseUpgraded = bPermanentUpgrade || bCombatUpgrade;
	return bUseUpgraded ? UpgradedEffects : BaseEffects;
}
