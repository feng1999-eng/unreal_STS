// Copyright unrealSTS. All Rights Reserved.

#include "Card/STSEffectExecutor.h"
#include "AbilitySystem/STSAbilitySystemComponent.h"
#include "AbilitySystem/STSAttributeSet.h"
#include "AbilitySystemInterface.h"
#include "Character/STSEnemyCharacter.h"
#include "Combat/STSCombatGameState.h"
#include "Core/STSGameplayTags.h"
#include "Effects/STSGameplayEffectLibrary.h"

namespace STSEffectExecutorInternal
{
	static USTSAbilitySystemComponent* GetASCFromActor(AActor* Actor)
	{
		if (!Actor)
		{
			return nullptr;
		}

		if (const IAbilitySystemInterface* ASI = Cast<IAbilitySystemInterface>(Actor))
		{
			return Cast<USTSAbilitySystemComponent>(ASI->GetAbilitySystemComponent());
		}

		return nullptr;
	}

	static ESTSCardTargetType ResolveTargetType(const FSTSCardEffect& Effect, ESTSCardTargetType DefaultTarget)
	{
		return Effect.TargetOverride != ESTSCardTargetType::None
			? Effect.TargetOverride
			: DefaultTarget;
	}
}

void USTSEffectExecutor::ExecuteEffects(
	const TArray<FSTSCardEffect>& Effects,
	USTSAbilitySystemComponent* SourceASC,
	AActor* TargetActor,
	ASTSCombatGameState* CombatGameState)
{
	for (const FSTSCardEffect& Effect : Effects)
	{
		const ESTSCardTargetType TargetType = STSEffectExecutorInternal::ResolveTargetType(
			Effect,
			ESTSCardTargetType::SingleEnemy);

		switch (TargetType)
		{
		case ESTSCardTargetType::Self:
			ExecuteEffect(Effect, SourceASC, SourceASC);
			break;

		case ESTSCardTargetType::SingleEnemy:
		case ESTSCardTargetType::None:
			ExecuteEffect(
				Effect,
				SourceASC,
				STSEffectExecutorInternal::GetASCFromActor(TargetActor));
			break;

		case ESTSCardTargetType::AllEnemies:
			if (CombatGameState)
			{
				for (ASTSEnemyCharacter* Enemy : CombatGameState->GetLivingEnemies())
				{
					ExecuteEffect(
						Effect,
						SourceASC,
						STSEffectExecutorInternal::GetASCFromActor(Enemy));
				}
			}
			break;

		case ESTSCardTargetType::RandomEnemy:
			if (CombatGameState)
			{
				const TArray<ASTSEnemyCharacter*> LivingEnemies = CombatGameState->GetLivingEnemies();
				if (LivingEnemies.Num() > 0)
				{
					const int32 Index = FMath::RandRange(0, LivingEnemies.Num() - 1);
					ExecuteEffect(
						Effect,
						SourceASC,
						STSEffectExecutorInternal::GetASCFromActor(LivingEnemies[Index]));
				}
			}
			break;

		default:
			break;
		}
	}
}

void USTSEffectExecutor::ExecuteEffect_Implementation(
	const FSTSCardEffect& Effect,
	USTSAbilitySystemComponent* SourceASC,
	USTSAbilitySystemComponent* TargetASC)
{
	if (!SourceASC)
	{
		return;
	}

	switch (Effect.EffectType)
	{
	case ESTSCardEffectType::Damage:
		if (TargetASC)
		{
			const FGameplayEffectSpecHandle Spec = USTSGameplayEffectLibrary::MakeDamageSpec(
				SourceASC,
				TargetASC,
				Effect.Magnitude);
			USTSGameplayEffectLibrary::ApplySpecToTarget(SourceASC, TargetASC, Spec);
		}
		break;

	case ESTSCardEffectType::Block:
		SourceASC->ApplyModToAttribute(
			USTSAttributeSet::GetBlockAttribute(),
			EGameplayModOp::Additive,
			Effect.Magnitude);
		break;

	case ESTSCardEffectType::Heal:
		if (TargetASC)
		{
			TargetASC->ApplyModToAttribute(
				USTSAttributeSet::GetHealthAttribute(),
				EGameplayModOp::Additive,
				Effect.Magnitude);
		}
		break;

	case ESTSCardEffectType::GainEnergy:
		SourceASC->ApplyModToAttribute(
			USTSAttributeSet::GetEnergyAttribute(),
			EGameplayModOp::Additive,
			Effect.Magnitude);
		break;

	case ESTSCardEffectType::DrawCards:
		if (UWorld* World = SourceASC->GetWorld())
		{
			if (ASTSCombatGameState* CombatGS = World->GetGameState<ASTSCombatGameState>())
			{
				CombatGS->DrawCards(FMath::RoundToInt(Effect.Magnitude));
			}
		}
		break;

	case ESTSCardEffectType::ApplyStatus:
		if (TargetASC)
		{
			if (Effect.StatusTag == STSGameplayTags::Status_Poison)
			{
				TargetASC->ApplyModToAttribute(
					USTSAttributeSet::GetPoisonAttribute(),
					EGameplayModOp::Additive,
					Effect.Magnitude);
			}
			else if (Effect.StatusTag == STSGameplayTags::Status_Strength)
			{
				TargetASC->ApplyModToAttribute(
					USTSAttributeSet::GetStrengthAttribute(),
					EGameplayModOp::Additive,
					Effect.Magnitude);
			}
			else if (Effect.StatusTag.IsValid())
			{
				TargetASC->AddLooseGameplayTag(Effect.StatusTag);
			}
		}
		break;

	case ESTSCardEffectType::Custom:
	default:
		break;
	}
}
