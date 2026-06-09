// Copyright unrealSTS. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/STSAbilitySet.h"
#include "STSCombatCharacter.generated.h"

class USTSAbilitySystemComponent;
class USTSAttributeSet;

UCLASS(Abstract, Blueprintable, BlueprintType)
class STSFRAMEWORK_API ASTSCombatCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ASTSCombatCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "STS|Character")
	void InitializeAbilitySystem();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "STS|Character")
	void GrantAbilitySets(const TArray<USTSAbilitySet*>& AbilitySets);

	UFUNCTION(BlueprintCallable, Category = "STS|Character")
	void SetCombatAttributes(float InMaxHealth, float InCurrentHealth);

	UFUNCTION(BlueprintCallable, Category = "STS|Character")
	virtual void GrantDefaultCombatAbilities();

	UFUNCTION(BlueprintImplementableEvent, Category = "STS|Character", meta = (DisplayName = "On Ability System Initialized"))
	void K2_OnAbilitySystemInitialized();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "STS|Ability")
	TObjectPtr<USTSAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<USTSAttributeSet> AttributeSet;

	UPROPERTY(BlueprintReadOnly, Category = "STS|Ability")
	FSTSGrantedAbilitySetHandles GrantedAbilitySetHandles;
};
