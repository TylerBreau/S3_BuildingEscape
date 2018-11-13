// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class S3_BuildingEscapeTarget : TargetRules
{
	public S3_BuildingEscapeTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		ExtraModuleNames.AddRange( new string[] { "S3_BuildingEscape" } );
	}
}
