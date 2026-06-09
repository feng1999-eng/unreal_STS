// Copyright unrealSTS. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "GameplayAbilitySpec.h"
#include "ActiveGameplayEffectHandle.h"
#include "STSAbilitySet.generated.h"

class UGameplayAbility;
class UGameplayEffect;
class UAbilitySystemComponent;

USTRUCT(BlueprintType)
struct STSFRAMEWORK_API FSTSAbilitySet_GameplayAbility
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability")
	TSubclassOf<UGameplayAbility> Ability = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability")
	int32 AbilityLevel = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability", meta = (Categories = "STS.Action"))
	FGameplayTag ActionTag;
};

USTRUCT(BlueprintType)
struct STSFRAMEWORK_API FSTSAbilitySet_GameplayEffect
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effect")
	TSubclassOf<UGameplayEffect> Effect = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effect")
	float EffectLevel = 1.f;
};

USTRUCT(BlueprintType)
struct STSFRAMEWORK_API FSTSGrantedAbilitySetHandles
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "STS")
	TArray<FGameplayAbilitySpecHandle> AbilitySpecHandles;

	UPROPERTY(BlueprintReadOnly, Category = "STS")
	TArray<FActiveGameplayEffectHandle> GameplayEffectHandles;
};

UCLASS(BlueprintType, Const)
class STSFRAMEWORK_API USTSAbilitySet : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Gameplay Abilities")
	TArray<FSTSAbilitySet_GameplayAbility> GrantedAbilities;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Gameplay Effects")
	TArray<FSTSAbilitySet_GameplayEffect> GrantedEffects;

	void GiveToAbilitySystem(UAbilitySystemComponent* ASC, FSTSGrantedAbilitySetHandles* OutHandles) const;
	void RemoveFromAbilitySystem(UAbilitySystemComponent* ASC, const FSTSGrantedAbilitySetHandles& Handles) const;
};
