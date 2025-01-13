using UnrealBuildTool;

public class EditorTests : ModuleRules
{
	public EditorTests(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new[] { "Core" });
		PrivateDependencyModuleNames.AddRange(new[] { "CoreUObject", "Engine", "UnrealEd", "FunctionalTesting", "UserInterface" });
	}
}