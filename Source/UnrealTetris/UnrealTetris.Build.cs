using UnrealBuildTool;

public class UnrealTetris : ModuleRules
{
	public UnrealTetris(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		bEnableExceptions = true;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"UMG"
		});

		PrivateDependencyModuleNames.AddRange(new string[] {
			"RenderCore",
			"RHI"
		});
	}
}