// Copyright unrealSTS. All Rights Reserved.

#include "Map/STSMapGenerator.h"
#include "Map/STSActConfigData.h"

FSTSMapGraph USTSMapGenerator::GenerateMapForAct_Implementation(const USTSActConfigData* ActConfig)
{
	FSTSMapGraph Graph;
	if (ActConfig)
	{
		Graph.ActIndex = ActConfig->ActIndex;
	}
	return Graph;
}
