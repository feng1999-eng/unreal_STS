// Copyright unrealSTS. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "STSGameModeBase.h"
#include "STSMapGameMode.generated.h"

UCLASS(Blueprintable, BlueprintType)
class UNREALSTS_API ASTSMapGameMode : public ASTSGameModeBase
{
	GENERATED_BODY()

public:
	ASTSMapGameMode();

protected:
	virtual void StartPlay() override;

	UFUNCTION(BlueprintImplementableEvent, Category = "STS|Map", meta = (DisplayName = "On Map Started"))
	void K2_OnMapStarted();
};
