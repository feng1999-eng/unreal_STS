// Copyright unrealSTS. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "STSGameInstance.generated.h"

class USTSRunSubsystem;

UCLASS()
class UNREALSTS_API USTSGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "STS|Run")
	USTSRunSubsystem* GetSTSRunSubsystem() const;
};
