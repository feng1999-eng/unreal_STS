// Copyright unrealSTS. All Rights Reserved.

#include "Combat/STSDamageExecution.h"
#include "AbilitySystem/STSAttributeSet.h"
#include "Core/STSGameplayTags.h"

USTSDamageExecution::USTSDamageExecution()
{
}

void USTSDamageExecution::Execute_Implementation(
	const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();
	float Damage = Spec.GetSetByCallerMagnitude(STSGameplayTags::Data_Damage, false, 0.f);
	if (Damage <= 0.f)
	{
		return;
	}

	UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
	UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();
	if (!TargetASC)
	{
		return;
	}

	if (SourceASC)
	{
		Damage += SourceASC->GetNumericAttribute(USTSAttributeSet::GetStrengthAttribute());
	}

	if (TargetASC->HasMatchingGameplayTag(STSGameplayTags::Status_Vulnerable))
	{
		Damage *= 1.5f;
	}

	if (SourceASC && SourceASC->HasMatchingGameplayTag(STSGameplayTags::Status_Weak))
	{
		Damage *= 0.75f;
	}

	const float Block = TargetASC->GetNumericAttribute(USTSAttributeSet::GetBlockAttribute());
	const float BlockDamage = FMath::Min(Block, Damage);
	const float HealthDamage = Damage - BlockDamage;

	if (BlockDamage > 0.f)
	{
		OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(
			USTSAttributeSet::GetBlockAttribute(),
			EGameplayModOp::Additive,
			-BlockDamage));
	}

	if (HealthDamage > 0.f)
	{
		OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(
			USTSAttributeSet::GetHealthAttribute(),
			EGameplayModOp::Additive,
			-HealthDamage));
	}
}
