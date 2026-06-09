// Copyright unrealSTS. All Rights Reserved.

#include "Effects/STSGameplayEffectLibrary.h"
#include "AbilitySystem/STSAbilitySystemComponent.h"
#include "AbilitySystem/STSAttributeSet.h"
#include "Combat/STSDamageExecution.h"
#include "Core/STSGameplayTags.h"
#include "GameplayEffect.h"

namespace STSInternalEffect
{
	static TObjectPtr<UGameplayEffect> DamageEffect;

	TSubclassOf<UGameplayEffect> ToEffectClass(UGameplayEffect* Effect)
	{
		return Effect ? TSubclassOf<UGameplayEffect>(Effect->GetClass()) : TSubclassOf<UGameplayEffect>();
	}
}

UGameplayEffect* USTSGameplayEffectLibrary::GetOrCreateDamageEffect()
{
	if (STSInternalEffect::DamageEffect)
	{
		return STSInternalEffect::DamageEffect;
	}

	UGameplayEffect* Effect = NewObject<UGameplayEffect>(
		GetTransientPackage(),
		USTSGameplayEffectLibrary::StaticClass(),
		TEXT("GE_STS_Damage_Exec"),
		RF_Transient);

	Effect->DurationPolicy = EGameplayEffectDurationType::Instant;

	FGameplayEffectExecutionDefinition Execution;
	Execution.CalculationClass = USTSDamageExecution::StaticClass();
	Effect->Executions.Add(Execution);

	STSInternalEffect::DamageEffect = Effect;
	return Effect;
}

FGameplayEffectSpecHandle USTSGameplayEffectLibrary::MakeDamageSpec(
	USTSAbilitySystemComponent* SourceASC,
	USTSAbilitySystemComponent* TargetASC,
	float DamageMagnitude)
{
	if (!SourceASC || !TargetASC)
	{
		return FGameplayEffectSpecHandle();
	}

	const FGameplayEffectContextHandle Context = SourceASC->MakeEffectContext();
	const FGameplayEffectSpecHandle SpecHandle = SourceASC->MakeOutgoingSpec(
		STSInternalEffect::ToEffectClass(GetOrCreateDamageEffect()),
		1.f,
		Context);

	if (SpecHandle.IsValid())
	{
		SpecHandle.Data->SetSetByCallerMagnitude(STSGameplayTags::Data_Damage, DamageMagnitude);
	}

	return SpecHandle;
}

FGameplayEffectSpecHandle USTSGameplayEffectLibrary::MakeHealSpec(
	USTSAbilitySystemComponent* SourceASC,
	USTSAbilitySystemComponent* TargetASC,
	float HealMagnitude)
{
	return MakeSetAttributeSpec(TargetASC, USTSAttributeSet::GetHealthAttribute(), HealMagnitude);
}

FGameplayEffectSpecHandle USTSGameplayEffectLibrary::MakeBlockSpec(
	USTSAbilitySystemComponent* SourceASC,
	float BlockMagnitude)
{
	return MakeSetAttributeSpec(SourceASC, USTSAttributeSet::GetBlockAttribute(), BlockMagnitude);
}

FGameplayEffectSpecHandle USTSGameplayEffectLibrary::MakeEnergyCostSpec(
	USTSAbilitySystemComponent* SourceASC,
	float CostMagnitude)
{
	return MakeSetAttributeSpec(SourceASC, USTSAttributeSet::GetEnergyAttribute(), -CostMagnitude);
}

FGameplayEffectSpecHandle USTSGameplayEffectLibrary::MakeSetAttributeSpec(
	USTSAbilitySystemComponent* SourceASC,
	FGameplayAttribute Attribute,
	float Value)
{
	return MakeSetAttributeSpec(SourceASC, Attribute, Value, STSGameplayTags::Data_Block);
}

FGameplayEffectSpecHandle USTSGameplayEffectLibrary::MakeSetAttributeSpec(
	USTSAbilitySystemComponent* SourceASC,
	FGameplayAttribute Attribute,
	float Value,
	FGameplayTag MagnitudeTag)
{
	// Non-damage attribute changes are applied directly in STSEffectExecutor.
	return FGameplayEffectSpecHandle();
}

void USTSGameplayEffectLibrary::ApplySpecToTarget(
	USTSAbilitySystemComponent* SourceASC,
	USTSAbilitySystemComponent* TargetASC,
	const FGameplayEffectSpecHandle& SpecHandle)
{
	if (!SourceASC || !TargetASC || !SpecHandle.IsValid())
	{
		return;
	}

	SourceASC->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), TargetASC);
}
