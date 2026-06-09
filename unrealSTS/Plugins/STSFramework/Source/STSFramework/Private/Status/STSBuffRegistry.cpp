// Copyright unrealSTS. All Rights Reserved.

#include "Status/STSBuffRegistry.h"
#include "Status/STSBuffDefinition.h"

USTSBuffDefinition* USTSBuffRegistry::FindBuffDefinition(FGameplayTag BuffTag) const
{
	for (USTSBuffDefinition* Definition : BuffDefinitions)
	{
		if (Definition && Definition->BuffTag == BuffTag)
		{
			return Definition;
		}
	}

	return nullptr;
}
