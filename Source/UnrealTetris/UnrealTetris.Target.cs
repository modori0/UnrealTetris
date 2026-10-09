using UnrealBuildTool;

public class UnrealTetrisTarget : TargetRules
{
	public UnrealTetrisTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettingsVersion = BuildSettingsVersion.V5;
		ExtraModuleNames.AddRange( new string[] { "UnrealTetris" } );
	}
}