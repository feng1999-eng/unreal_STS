// Copyright unrealSTS. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "GameplayTagContainer.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "STSRelicManager.generated.h"

class USTSRelicData;
class USTSAbilitySystemComponent;

UCLASS(Blueprintable, BlueprintType)
class STSFRAMEWORK_API USTSRelicManager : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "STS|Relic")
	void Initialize(USTSAbilitySystemComponent* InPlayerASC);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "STS|Relic")
	void HandleGameplayEvent(FGameplayTag EventTag, const FGameplayEventData& Payload);

	UFUNCTION(BlueprintImplementableEvent, Category = "STS|Relic", meta = (DisplayName = "On Relic Event"))
	void K2_OnRelicEvent(FGameplayTag EventTag);

protected:
	UPROPERTY()
	TObjectPtr<USTSAbilitySystemComponent> PlayerASC;
};
