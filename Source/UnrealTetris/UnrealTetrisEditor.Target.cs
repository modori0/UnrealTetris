using UnrealBuildTool;

public class UnrealTetrisEditorTarget : TargetRules
{
	public UnrealTetrisEditorTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettingsVersion = BuildSettingsVersion.V5;
		ExtraModuleNames.AddRange( new string[] { "UnrealTetris" } );
	}
}