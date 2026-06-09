// Copyright unrealSTS. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Combat/STSEncounterData.h"
#include "STSMapTypes.generated.h"

UENUM(BlueprintType)
enum class ESTSMapNodeType : uint8
{
	Combat,
	Elite,
	Shop,
	Rest,
	Treasure,
	Boss
};

UENUM(BlueprintType)
enum class ESTSMapNodeState : uint8
{
	Locked,
	Available,
	Cleared
};

USTRUCT(BlueprintType)
struct STSFRAMEWORK_API FSTSMapNode
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "STS|Map")
	FName NodeId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "STS|Map")
	int32 LayerIndex = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "STS|Map")
	ESTSMapNodeType Type = ESTSMapNodeType::Combat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "STS|Map")
	ESTSMapNodeState State = ESTSMapNodeState::Locked;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "STS|Map")
	TObjectPtr<USTSEncounterData> Encounter = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "STS|Map")
	TArray<FName> NextNodeIds;
};

USTRUCT(BlueprintType)
struct STSFRAMEWORK_API FSTSMapGraph
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "STS|Map")
	int32 ActIndex = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "STS|Map")
	TArray<FSTSMapNode> Nodes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "STS|Map")
	FName EntryNodeId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "STS|Map")
	FName BossNodeId;

	bool FindNodeById(FName NodeId, FSTSMapNode& OutNode) const
	{
		for (const FSTSMapNode& Node : Nodes)
		{
			if (Node.NodeId == NodeId)
			{
				OutNode = Node;
				return true;
			}
		}
		return false;
	}
};
