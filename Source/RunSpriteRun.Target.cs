// Copyright KittenGames

using UnrealBuildTool;
using System.Collections.Generic;

public class RunSpriteRunTarget : TargetRules
{
	public RunSpriteRunTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "RunSpriteRun" } );
	}
}
