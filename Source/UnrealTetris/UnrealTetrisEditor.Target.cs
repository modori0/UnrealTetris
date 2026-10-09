using UnrealBuildTool;

public class UnrealTetrisEditorTarget : TargetRules
{
	public UnrealTetrisEditorTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		BuildEnvironment = TargetBuildEnvironment.Unique;
		ExtraModuleNames.AddRange( new string[] { "UnrealTetris" } );
	}
}