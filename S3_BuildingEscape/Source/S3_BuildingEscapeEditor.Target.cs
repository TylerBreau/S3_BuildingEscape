// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class S3_BuildingEscapeEditorTarget : TargetRules
{
	public S3_BuildingEscapeEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

		ExtraModuleNames.AddRange( new string[] { "S3_BuildingEscape" } );
	}
}
