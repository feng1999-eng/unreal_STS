// Copyright unrealSTS. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "STSGameModeBase.h"
#include "STSMainMenuGameMode.generated.h"

UCLASS(Blueprintable, BlueprintType)
class UNREALSTS_API ASTSMainMenuGameMode : public ASTSGameModeBase
{
	GENERATED_BODY()

public:
	ASTSMainMenuGameMode();

protected:
	virtual void StartPlay() override;

	UFUNCTION(BlueprintImplementableEvent, Category = "STS|Menu", meta = (DisplayName = "On Main Menu Started"))
	void K2_OnMainMenuStarted();
};
