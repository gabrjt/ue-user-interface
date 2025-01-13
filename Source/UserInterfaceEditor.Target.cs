// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class UserInterfaceEditorTarget : TargetRules
{
	public UserInterfaceEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V5;

		ExtraModuleNames.AddRange(new[] { "UserInterface", "EditorTests" });
	}
}