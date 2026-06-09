// Copyright unrealSTS. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "STSPlayerController.generated.h"

UCLASS(Blueprintable, BlueprintType)
class UNREALSTS_API ASTSPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ASTSPlayerController();

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent, Category = "STS|Player", meta = (DisplayName = "On Player Controller Ready"))
	void K2_OnPlayerControllerReady();
};
