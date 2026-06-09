// Copyright unrealSTS. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/STSGameplayAbility.h"
#include "STSGameplayAbility_PlayCard.generated.h"

class USTSCardData;

UCLASS(Blueprintable)
class STSFRAMEWORK_API USTSGameplayAbility_PlayCard : public USTSGameplayAbility
{
	GENERATED_BODY()

public:
	USTSGameplayAbility_PlayCard();

	virtual void ActivateAbility(
		const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		const FGameplayEventData* TriggerEventData) override;

	virtual bool CanActivateAbility(
		const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayTagContainer* SourceTags,
		const FGameplayTagContainer* TargetTags,
		FGameplayTagContainer* OptionalRelevantTags) const override;

	/** 解析 CardData 后执行效果；C++ 默认空，可在 BP 子类或后续 C++ 中实现。 */
	UFUNCTION(BlueprintImplementableEvent, Category = "STS|Card", meta = (DisplayName = "Execute Card Effects"))
	void K2_ExecuteCardEffects(const USTSCardData* CardData, AActor* TargetActor);

	/** 额外出牌校验（能量/Phase 等之上）。 */
	UFUNCTION(BlueprintNativeEvent, Category = "STS|Card", meta = (DisplayName = "Can Play Card"))
	bool K2_CanPlayCard(const USTSCardData* CardData, AActor* TargetActor) const;
	virtual bool K2_CanPlayCard_Implementation(const USTSCardData* CardData, AActor* TargetActor) const;
};
