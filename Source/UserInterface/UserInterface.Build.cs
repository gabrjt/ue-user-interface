// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class UserInterface : ModuleRules
{
	public UserInterface(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new[] { "Core", "CoreUObject", "Engine", "InputCore", "ModelViewViewModel" });
		PrivateDependencyModuleNames.AddRange(new[] { "Slate", "SlateCore" });
	}
}