using UnrealBuildTool;

public class UnrealTetrisEditorTarget : TargetRules
{
	public UnrealTetrisEditorTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettingsVersion = BuildSettingsVersion.V5;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
		CppStandard = CppStandardVersion.Cpp20;
		ExtraModuleNames.AddRange( new string[] { "UnrealTetris" } );
	}
}