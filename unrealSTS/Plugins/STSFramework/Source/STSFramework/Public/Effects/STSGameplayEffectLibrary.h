// Copyright unrealSTS. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "STSGameplayEffectLibrary.generated.h"

class UGameplayEffect;
class USTSAbilitySystemComponent;
class USTSAttributeSet;

UCLASS()
class STSFRAMEWORK_API USTSGameplayEffectLibrary : public UObject
{
	GENERATED_BODY()

public:
	static FGameplayEffectSpecHandle MakeDamageSpec(
		USTSAbilitySystemComponent* SourceASC,
		USTSAbilitySystemComponent* TargetASC,
		float DamageMagnitude);

	static FGameplayEffectSpecHandle MakeHealSpec(
		USTSAbilitySystemComponent* SourceASC,
		USTSAbilitySystemComponent* TargetASC,
		float HealMagnitude);

	static FGameplayEffectSpecHandle MakeBlockSpec(
		USTSAbilitySystemComponent* SourceASC,
		float BlockMagnitude);

	static FGameplayEffectSpecHandle MakeEnergyCostSpec(
		USTSAbilitySystemComponent* SourceASC,
		float CostMagnitude);

	static FGameplayEffectSpecHandle MakeSetAttributeSpec(
		USTSAbilitySystemComponent* SourceASC,
		FGameplayAttribute Attribute,
		float Value);

	static FGameplayEffectSpecHandle MakeSetAttributeSpec(
		USTSAbilitySystemComponent* SourceASC,
		FGameplayAttribute Attribute,
		float Value,
		FGameplayTag MagnitudeTag);

	static void ApplySpecToTarget(
		USTSAbilitySystemComponent* SourceASC,
		USTSAbilitySystemComponent* TargetASC,
		const FGameplayEffectSpecHandle& SpecHandle);

private:
	static UGameplayEffect* GetOrCreateDamageEffect();
};
