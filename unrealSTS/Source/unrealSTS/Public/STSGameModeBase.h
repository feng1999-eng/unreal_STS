// Copyright unrealSTS. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "STSGameModeBase.generated.h"

UCLASS(Abstract, Blueprintable, BlueprintType)
class UNREALSTS_API ASTSGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASTSGameModeBase();

protected:
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

	UFUNCTION(BlueprintImplementableEvent, Category = "STS|Game", meta = (DisplayName = "On Game Initialized"))
	void K2_OnGameInitialized();
};
