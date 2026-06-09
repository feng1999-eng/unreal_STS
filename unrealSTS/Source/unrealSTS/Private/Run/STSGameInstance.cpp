// Copyright unrealSTS. All Rights Reserved.

#include "Run/STSGameInstance.h"
#include "Run/STSRunSubsystem.h"

USTSRunSubsystem* USTSGameInstance::GetSTSRunSubsystem() const
{
	return GetSubsystem<USTSRunSubsystem>();
}
