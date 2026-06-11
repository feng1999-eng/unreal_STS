// Copyright unrealSTS. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "STSPlayerController.generated.h"

/** 战斗关卡 PlayerController；PIE 阶段绑定调试按键，正式 UI 就绪后可换子类。 */
UCLASS(Blueprintable, BlueprintType)
class UNREALSTS_API ASTSPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ASTSPlayerController();

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	UFUNCTION(BlueprintImplementableEvent, Category = "STS|Player", meta = (DisplayName = "On Player Controller Ready"))
	void K2_OnPlayerControllerReady();

	void HandleDebugEndTurn();
	void HandleDebugPrintState();
	/** 将 Hand[HandIndex] 打出，目标为第一个存活敌人。 */
	void HandleDebugPlayHandCard(int32 HandIndex);
	void HandlePlayCardKey0() { HandleDebugPlayHandCard(0); }
	void HandlePlayCardKey1() { HandleDebugPlayHandCard(1); }
	void HandlePlayCardKey2() { HandleDebugPlayHandCard(2); }
	void HandlePlayCardKey3() { HandleDebugPlayHandCard(3); }
	void HandlePlayCardKey4() { HandleDebugPlayHandCard(4); }

	/** 在 Log 与屏幕显示 Phase1/2 调试按键说明。 */
	void ShowDebugHelp() const;
};
