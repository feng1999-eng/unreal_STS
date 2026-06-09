// Copyright unrealSTS. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "STSCardTypes.generated.h"

UENUM(BlueprintType)
enum class ESTSCardEffectType : uint8
{
	Damage,
	Block,
	Heal,
	DrawCards,
	GainEnergy,
	ApplyStatus,
	Custom
};

UENUM(BlueprintType)
enum class ESTSCardTargetType : uint8
{
	Self,
	SingleEnemy,
	AllEnemies,
	RandomEnemy,
	None
};

/** Data-driven effect entry; resolved by STSEffectExecutor (implementation deferred). */
USTRUCT(BlueprintType)
struct STSFRAMEWORK_API FSTSCardEffect
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "STS")
	ESTSCardEffectType EffectType = ESTSCardEffectType::Damage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "STS")
	float Magnitude = 0.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "STS", meta = (Categories = "STS.Status"))
	FGameplayTag StatusTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "STS")
	ESTSCardTargetType TargetOverride = ESTSCardTargetType::None;
};
