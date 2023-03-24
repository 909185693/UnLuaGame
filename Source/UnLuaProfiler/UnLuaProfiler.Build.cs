// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.IO;

public class UnLuaProfiler : ModuleRules
{
    public UnLuaProfiler(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
        // enable exception
        bEnableExceptions = true;
        bEnableUndefinedIdentifierWarnings = false;
#if UE_5_2_OR_LATER
        IWYUSupport = IWYUSupport.None;
#else
        bEnforceIWYU = false;
#endif
#if UE_4_21_OR_LATER
        PublicDefinitions.Add("ENABLE_UNLUAPROFILER");
#else
        Definitions.Add("ENABLE_UNLUAPROFILER");
#endif
        
        PublicIncludePaths.AddRange(
            new string []
            {
                //"UnLua/Public",
            }
        );

        PrivateIncludePaths.AddRange(
            new string[]
            {
                "UnLuaProfiler/Editor",
                "UnLuaProfiler/LuaCore",
                "UnLuaProfiler/Runtime",
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore",
                "UMG",
                "EditorStyle",
                "InputCore",
                "Networking",
                "Sockets",
                "Lua",
                "UnLua",
				// ... add private dependencies that you statically link with here ...	
			}
        );

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "UMG",
                "Lua",
                "UnLua",
				// ... add other public dependencies that you statically link with here ...
			}
        );

        if (Target.Type == TargetRules.TargetType.Editor)
        {
            PrivateDependencyModuleNames.Add("UnrealEd");
            PrivateDependencyModuleNames.Add("EditorStyle");
            PrivateDependencyModuleNames.Add("LevelEditor");
        }
    }
}
