// Copyright unrealSTS. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Card/STSCardTypes.h"
#include "STSIntentComponent.generated.h"

USTRUCT(BlueprintType)
struct STSFRAMEWORK_API FSTSEnemyIntent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "STS|Intent")
	FText DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "STS|Intent")
	TArray<FSTSCardEffect> Effects;
};

UCLASS(ClassGroup = (STS), meta = (BlueprintSpawnableComponent))
class STSFRAMEWORK_API USTSIntentComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, Category = "STS|Intent")
	FSTSEnemyIntent CurrentIntent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "STS|Intent")
	TArray<FSTSEnemyIntent> IntentPattern;

	UFUNCTION(BlueprintCallable, Category = "STS|Intent")
	virtual void RollNextIntent();

protected:
	int32 CurrentPatternIndex = 0;
};
