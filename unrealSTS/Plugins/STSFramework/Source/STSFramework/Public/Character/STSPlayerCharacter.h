// Copyright unrealSTS. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Character/STSCombatCharacter.h"
#include "STSPlayerCharacter.generated.h"

class USTSCharacterData;

UCLASS(Blueprintable, BlueprintType)
class STSFRAMEWORK_API ASTSPlayerCharacter : public ASTSCombatCharacter
{
	GENERATED_BODY()

public:
	ASTSPlayerCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "STS|Character")
	void InitializeFromCharacterData(const USTSCharacterData* CharacterData);

	UFUNCTION(BlueprintImplementableEvent, Category = "STS|Character", meta = (DisplayName = "On Character Data Applied"))
	void K2_OnCharacterDataApplied(const USTSCharacterData* CharacterData);
};
