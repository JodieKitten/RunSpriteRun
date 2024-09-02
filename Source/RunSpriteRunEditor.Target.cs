// Copyright KittenGames

using UnrealBuildTool;
using System.Collections.Generic;

public class RunSpriteRunEditorTarget : TargetRules
{
	public RunSpriteRunEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "RunSpriteRun" } );
	}
}
