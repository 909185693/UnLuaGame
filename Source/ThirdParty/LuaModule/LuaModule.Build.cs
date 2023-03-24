// Copyright 2022 CQUnreal. All Rights Reserved.

using System.IO;
using UnrealBuildTool;

public class LuaModule : ModuleRules
{
	public LuaModule(ReadOnlyTargetRules Target) : base(Target)
	{
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] {
            "Core",
            "Engine",
            "Lua",
            "UnLua"
        });
    }
}
