// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class DisablingGamma : ModuleRules
{
	public DisablingGamma(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay",
            "Slate", "SlateCore", });
	}
}
