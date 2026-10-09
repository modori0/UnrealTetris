using UnrealBuildTool;

public class UnrealTetrisTarget : TargetRules
{
	public UnrealTetrisTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		ExtraModuleNames.AddRange( new string[] { "UnrealTetris" } );
	}
}