// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class unrealSTS : ModuleRules
{
	public unrealSTS(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"STSFramework",
			"UMG"
		});

		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"GameplayAbilities",
			"GameplayTags"
		});
	}
}
