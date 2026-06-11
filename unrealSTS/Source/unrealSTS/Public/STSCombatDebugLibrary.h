// Copyright unrealSTS. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "STSCombatDebugLibrary.generated.h"

class ASTSPlayerController;

/** Phase 1/2 PIE 调试：键盘/控制台驱动出牌与回合，替代正式 Combat HUD。 */
UCLASS()
class UNREALSTS_API USTSCombatDebugLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/** 调用 CombatGameState::EndPlayerTurn。 */
	UFUNCTION(BlueprintCallable, Category = "STS|Debug", meta = (WorldContext = "WorldContextObject"))
	static void DebugEndPlayerTurn(const UObject* WorldContextObject);

	/** 打出 Hand[HandIndex]，目标为第一个存活敌人。 */
	UFUNCTION(BlueprintCallable, Category = "STS|Debug", meta = (WorldContext = "WorldContextObject"))
	static void DebugPlayHandCard(const UObject* WorldContextObject, int32 HandIndex);

	/** 输出阶段、牌堆、HP/Block/Energy、手牌列表到 Log 与屏幕。 */
	UFUNCTION(BlueprintCallable, Category = "STS|Debug", meta = (WorldContext = "WorldContextObject"))
	static void DebugPrintCombatState(const UObject* WorldContextObject);

	/** 注册 sts.EndTurn / sts.PlayCard / sts.DebugCombat 控制台命令（仅一次）。 */
	static void RegisterConsoleCommands();
};
