// Copyright unrealSTS. All Rights Reserved.

#include "Test/STSTestContentFactory.h"
#include "Card/STSCardData.h"
#include "Character/STSCharacterData.h"
#include "Character/STSEnemyData.h"
#include "Character/STSIntentComponent.h"
#include "Combat/STSEncounterData.h"
#include "Core/STSGameplayTags.h"

namespace STSTestContentInternal
{
	// 单例缓存，避免 PIE 重复创建 Transient 数据
	static TObjectPtr<USTSCharacterData> CharacterData;
	static TObjectPtr<USTSEncounterData> EncounterData;
	static TObjectPtr<USTSEnemyData> EnemyData;
	static TMap<FName, TObjectPtr<USTSCardData>> Cards;
}

// CardId: Strike | Defend | Bash | Poison | AoE
USTSCardData* USTSTestContentFactory::CreateTestCard(FName CardId)
{
	USTSCardData* Card = NewObject<USTSCardData>(
		GetTransientPackage(),
		USTSCardData::StaticClass(),
		CardId,
		RF_Transient);

	if (CardId == FName(TEXT("Strike")))
	{
		Card->DisplayName = FText::FromString(TEXT("Strike"));
		Card->CardTypeTag = STSGameplayTags::Card_Type_Attack;
		Card->RarityTag = STSGameplayTags::Card_Rarity_Basic;
		Card->BaseCost = 1;
		Card->UpgradedCost = 1;

		FSTSCardEffect Effect;
		Effect.EffectType = ESTSCardEffectType::Damage;
		Effect.Magnitude = 6.f;
		Effect.TargetOverride = ESTSCardTargetType::SingleEnemy;
		Card->BaseEffects.Add(Effect);
		Card->UpgradedEffects = Card->BaseEffects;
	}
	else if (CardId == FName(TEXT("Defend")))
	{
		Card->DisplayName = FText::FromString(TEXT("Defend"));
		Card->CardTypeTag = STSGameplayTags::Card_Type_Skill;
		Card->RarityTag = STSGameplayTags::Card_Rarity_Basic;
		Card->BaseCost = 1;

		FSTSCardEffect Effect;
		Effect.EffectType = ESTSCardEffectType::Block;
		Effect.Magnitude = 5.f;
		Effect.TargetOverride = ESTSCardTargetType::Self;
		Card->BaseEffects.Add(Effect);
		Card->UpgradedEffects = Card->BaseEffects;
	}
	else if (CardId == FName(TEXT("Bash")))
	{
		Card->DisplayName = FText::FromString(TEXT("Bash"));
		Card->CardTypeTag = STSGameplayTags::Card_Type_Attack;
		Card->RarityTag = STSGameplayTags::Card_Rarity_Common;
		Card->BaseCost = 2;

		FSTSCardEffect DamageEffect;
		DamageEffect.EffectType = ESTSCardEffectType::Damage;
		DamageEffect.Magnitude = 8.f;
		DamageEffect.TargetOverride = ESTSCardTargetType::SingleEnemy;
		Card->BaseEffects.Add(DamageEffect);

		FSTSCardEffect VulnerableEffect;
		VulnerableEffect.EffectType = ESTSCardEffectType::ApplyStatus;
		VulnerableEffect.Magnitude = 2.f;
		VulnerableEffect.StatusTag = STSGameplayTags::Status_Vulnerable;
		VulnerableEffect.TargetOverride = ESTSCardTargetType::SingleEnemy;
		Card->BaseEffects.Add(VulnerableEffect);
		Card->UpgradedEffects = Card->BaseEffects;
	}
	else if (CardId == FName(TEXT("Poison")))
	{
		Card->DisplayName = FText::FromString(TEXT("Poison Stab"));
		Card->CardTypeTag = STSGameplayTags::Card_Type_Attack;
		Card->RarityTag = STSGameplayTags::Card_Rarity_Common;
		Card->BaseCost = 1;

		FSTSCardEffect DamageEffect;
		DamageEffect.EffectType = ESTSCardEffectType::Damage;
		DamageEffect.Magnitude = 4.f;
		Card->BaseEffects.Add(DamageEffect);

		FSTSCardEffect PoisonEffect;
		PoisonEffect.EffectType = ESTSCardEffectType::ApplyStatus;
		PoisonEffect.Magnitude = 5.f;
		PoisonEffect.StatusTag = STSGameplayTags::Status_Poison;
		Card->BaseEffects.Add(PoisonEffect);
		Card->UpgradedEffects = Card->BaseEffects;
	}
	else if (CardId == FName(TEXT("AoE")))
	{
		Card->DisplayName = FText::FromString(TEXT("Cleave"));
		Card->CardTypeTag = STSGameplayTags::Card_Type_Attack;
		Card->RarityTag = STSGameplayTags::Card_Rarity_Common;
		Card->BaseCost = 1;

		FSTSCardEffect Effect;
		Effect.EffectType = ESTSCardEffectType::Damage;
		Effect.Magnitude = 4.f;
		Effect.TargetOverride = ESTSCardTargetType::AllEnemies;
		Card->BaseEffects.Add(Effect);
		Card->UpgradedEffects = Card->BaseEffects;
	}

	return Card;
}

// 缓存命中则直接返回，否则 CreateTestCard 并登记
USTSCardData* USTSTestContentFactory::GetTestCard(FName CardId)
{
	if (TObjectPtr<USTSCardData>* Found = STSTestContentInternal::Cards.Find(CardId))
	{
		return Found->Get();
	}

	USTSCardData* Card = CreateTestCard(CardId);
	STSTestContentInternal::Cards.Add(CardId, Card);
	return Card;
}

// 5 Strike + 4 Defend + Bash + Poison + Cleave
USTSCharacterData* USTSTestContentFactory::GetTestCharacterData()
{
	if (STSTestContentInternal::CharacterData)
	{
		return STSTestContentInternal::CharacterData;
	}

	USTSCharacterData* CharacterData = NewObject<USTSCharacterData>(
		GetTransientPackage(),
		USTSCharacterData::StaticClass(),
		TEXT("Test_Character_Ironclad"),
		RF_Transient);

	CharacterData->DisplayName = FText::FromString(TEXT("Test Ironclad"));
	CharacterData->StartingMaxHealth = 80.f;

	auto AddStarter = [CharacterData](FName CardId, int32 Count)
	{
		if (USTSCardData* Card = GetTestCard(CardId))
		{
			for (int32 Index = 0; Index < Count; ++Index)
			{
				CharacterData->StarterDeck.Add(Card);
			}
		}
	};

	AddStarter(FName(TEXT("Strike")), 5);
	AddStarter(FName(TEXT("Defend")), 4);
	AddStarter(FName(TEXT("Bash")), 1);
	AddStarter(FName(TEXT("Poison")), 1);
	AddStarter(FName(TEXT("AoE")), 1);

	STSTestContentInternal::CharacterData = CharacterData;
	return CharacterData;
}

// 单敌人 Cultist，意图在 InitializeFromEnemyData 时写入 IntentComponent
USTSEnemyData* USTSTestContentFactory::GetTestEnemyData()
{
	if (STSTestContentInternal::EnemyData)
	{
		return STSTestContentInternal::EnemyData;
	}

	USTSEnemyData* EnemyData = NewObject<USTSEnemyData>(
		GetTransientPackage(),
		USTSEnemyData::StaticClass(),
		TEXT("Test_Enemy_Cultist"),
		RF_Transient);

	EnemyData->DisplayName = FText::FromString(TEXT("Test Cultist"));
	EnemyData->MaxHealth = 48.f;

	FSTSEnemyIntent AttackIntent;
	AttackIntent.DisplayName = FText::FromString(TEXT("Attack"));
	FSTSCardEffect AttackEffect;
	AttackEffect.EffectType = ESTSCardEffectType::Damage;
	AttackEffect.Magnitude = 6.f;
	AttackEffect.TargetOverride = ESTSCardTargetType::SingleEnemy;
	AttackIntent.Effects.Add(AttackEffect);

	FSTSEnemyIntent DefendIntent;
	DefendIntent.DisplayName = FText::FromString(TEXT("Defend"));
	FSTSCardEffect BlockEffect;
	BlockEffect.EffectType = ESTSCardEffectType::Block;
	BlockEffect.Magnitude = 8.f;
	BlockEffect.TargetOverride = ESTSCardTargetType::Self;
	DefendIntent.Effects.Add(BlockEffect);

	EnemyData->IntentPattern = { AttackIntent, AttackIntent, DefendIntent };

	STSTestContentInternal::EnemyData = EnemyData;
	return EnemyData;
}

// 一场标准测试战：1× Cultist
USTSEncounterData* USTSTestContentFactory::GetTestEncounterData()
{
	if (STSTestContentInternal::EncounterData)
	{
		return STSTestContentInternal::EncounterData;
	}

	USTSEncounterData* EncounterData = NewObject<USTSEncounterData>(
		GetTransientPackage(),
		USTSEncounterData::StaticClass(),
		TEXT("Test_Encounter_Cultist"),
		RF_Transient);

	EncounterData->DisplayName = FText::FromString(TEXT("Test Cultist Encounter"));
	EncounterData->GoldReward = 15;

	FSTSEncounterSpawnEntry SpawnEntry;
	SpawnEntry.EnemyData = GetTestEnemyData();
	SpawnEntry.Count = 1;
	EncounterData->SpawnEntries.Add(SpawnEntry);

	STSTestContentInternal::EncounterData = EncounterData;
	return EncounterData;
}
