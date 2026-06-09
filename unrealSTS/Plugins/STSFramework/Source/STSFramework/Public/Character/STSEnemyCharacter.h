// Copyright unrealSTS. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Character/STSCombatCharacter.h"
#include "STSEnemyCharacter.generated.h"

class USTSEnemyData;
class USTSIntentComponent;

UCLASS(Blueprintable, BlueprintType)
class STSFRAMEWORK_API ASTSEnemyCharacter : public ASTSCombatCharacter
{
	GENERATED_BODY()

public:
	ASTSEnemyCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "STS|Character")
	void InitializeFromEnemyData(const USTSEnemyData* EnemyData);

	virtual void GrantDefaultCombatAbilities() override;

	UFUNCTION(BlueprintPure, Category = "STS|Character")
	USTSIntentComponent* GetIntentComponent() const { return IntentComponent; }

	UFUNCTION(BlueprintImplementableEvent, Category = "STS|Character", meta = (DisplayName = "On Enemy Data Applied"))
	void K2_OnEnemyDataApplied(const USTSEnemyData* EnemyData);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "STS|Intent")
	TObjectPtr<USTSIntentComponent> IntentComponent;
};
