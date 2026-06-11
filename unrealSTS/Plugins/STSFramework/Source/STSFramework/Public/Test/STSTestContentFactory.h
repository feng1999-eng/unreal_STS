// Copyright unrealSTS. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "STSTestContentFactory.generated.h"

class USTSCardData;
class USTSCharacterData;
class USTSEncounterData;
class USTSEnemyData;

/**
 * Phase 1/2 验证用内容工厂。
 * 在内存中创建 Transient DataAsset，无需 Content 目录下的 uasset。
 */
UCLASS()
class STSFRAMEWORK_API USTSTestContentFactory : public UObject
{
	GENERATED_BODY()

public:
	/** 测试角色：80 HP + 12 张起始牌（含 Strike/Defend/Bash/Poison/Cleave）。 */
	UFUNCTION(BlueprintCallable, Category = "STS|Test")
	static USTSCharacterData* GetTestCharacterData();

	/** 测试遭遇：1 个 Cultist，GoldReward=15。 */
	UFUNCTION(BlueprintCallable, Category = "STS|Test")
	static USTSEncounterData* GetTestEncounterData();

	/** 按 CardId 取单卡（Strike/Defend/Bash/Poison/AoE），首次创建后缓存。 */
	UFUNCTION(BlueprintCallable, Category = "STS|Test")
	static USTSCardData* GetTestCard(FName CardId);

	/** 测试敌人：48 HP，意图循环 攻6→攻6→防8。 */
	UFUNCTION(BlueprintCallable, Category = "STS|Test")
	static USTSEnemyData* GetTestEnemyData();

private:
	/** 根据 CardId 构造一张 Transient 卡牌数据。 */
	static USTSCardData* CreateTestCard(FName CardId);
};
