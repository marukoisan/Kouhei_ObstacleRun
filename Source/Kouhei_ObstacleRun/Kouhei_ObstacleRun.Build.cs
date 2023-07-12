// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Kouhei_ObstacleRun : ModuleRules
{
	public Kouhei_ObstacleRun(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput" });
	}
}
