// Copyright unrealSTS. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "STSBuffDefinition.generated.h"

class UGameplayEffect;

UENUM(BlueprintType)
enum class ESTSStackType : uint8
{
	None,
	Intensity,
	Count
};

UCLASS(BlueprintType, Const)
class STSFRAMEWORK_API USTSBuffDefinition : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "STS|Buff", meta = (Categories = "STS.Status"))
	FGameplayTag BuffTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "STS|Buff")
	TSubclassOf<UGameplayEffect> GameplayEffectClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "STS|Buff")
	ESTSStackType StackType = ESTSStackType::Count;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "STS|Buff", meta = (Categories = "STS.Status.Decay"))
	FGameplayTag DecayEventTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "STS|Buff")
	bool bBlockedByArtifact = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "STS|Buff")
	FText DisplayName;
};
