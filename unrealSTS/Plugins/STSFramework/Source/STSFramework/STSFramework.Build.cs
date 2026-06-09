// Copyright unrealSTS. All Rights Reserved.

using UnrealBuildTool;

public class STSFramework : ModuleRules
{
	public STSFramework(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"CoreUObject",
			"Engine",
			"GameplayTags",
			"GameplayTasks",
			"GameplayAbilities",
			"UMG"
		});

		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"NetCore"
		});
	}
}
