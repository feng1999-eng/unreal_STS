// Copyright unrealSTS. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "STSAbilitySystemComponent.generated.h"

class USTSCardData;

UCLASS(ClassGroup = (STS), meta = (BlueprintSpawnableComponent))
class STSFRAMEWORK_API USTSAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "STS|Ability")
	bool TryActivateAbilityByActionTag(const FGameplayTag& ActionTag);

	UFUNCTION(BlueprintCallable, Category = "STS|Ability")
	bool TryActivatePlayCardAbility(USTSCardData* CardData, AActor* TargetActor);
};
