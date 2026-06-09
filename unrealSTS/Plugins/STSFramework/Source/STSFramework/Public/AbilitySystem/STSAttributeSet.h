// Copyright unrealSTS. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "STSAttributeSet.generated.h"

#define STS_ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class STSFRAMEWORK_API USTSAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	USTSAttributeSet();

	UPROPERTY(BlueprintReadOnly, Category = "STS|Attributes", ReplicatedUsing = OnRep_Health)
	FGameplayAttributeData Health;
	STS_ATTRIBUTE_ACCESSORS(USTSAttributeSet, Health)

	UPROPERTY(BlueprintReadOnly, Category = "STS|Attributes", ReplicatedUsing = OnRep_MaxHealth)
	FGameplayAttributeData MaxHealth;
	STS_ATTRIBUTE_ACCESSORS(USTSAttributeSet, MaxHealth)

	UPROPERTY(BlueprintReadOnly, Category = "STS|Attributes", ReplicatedUsing = OnRep_Block)
	FGameplayAttributeData Block;
	STS_ATTRIBUTE_ACCESSORS(USTSAttributeSet, Block)

	UPROPERTY(BlueprintReadOnly, Category = "STS|Attributes", ReplicatedUsing = OnRep_Energy)
	FGameplayAttributeData Energy;
	STS_ATTRIBUTE_ACCESSORS(USTSAttributeSet, Energy)

	UPROPERTY(BlueprintReadOnly, Category = "STS|Attributes", ReplicatedUsing = OnRep_Poison)
	FGameplayAttributeData Poison;
	STS_ATTRIBUTE_ACCESSORS(USTSAttributeSet, Poison)

	UPROPERTY(BlueprintReadOnly, Category = "STS|Attributes", ReplicatedUsing = OnRep_Strength)
	FGameplayAttributeData Strength;
	STS_ATTRIBUTE_ACCESSORS(USTSAttributeSet, Strength)

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_Block(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_Energy(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_Poison(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_Strength(const FGameplayAttributeData& OldValue);
};
