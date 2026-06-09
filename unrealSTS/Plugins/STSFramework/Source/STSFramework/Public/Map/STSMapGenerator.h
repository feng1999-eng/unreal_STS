// Copyright unrealSTS. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Run/STSMapTypes.h"
#include "STSMapGenerator.generated.h"

class USTSActConfigData;

UCLASS(Blueprintable, BlueprintType)
class STSFRAMEWORK_API USTSMapGenerator : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "STS|Map")
	FSTSMapGraph GenerateMapForAct(const USTSActConfigData* ActConfig);
};
