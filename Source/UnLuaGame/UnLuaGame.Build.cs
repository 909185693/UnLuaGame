// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using System;
using System.IO;
using System.Collections.Generic;
using UnrealBuildTool;
#if UE_5_0_OR_LATER
using EpicGames.Core;
#else
using Tools.DotNETCommon;
#endif

struct UnLuaGameModule
{
    public UnLuaGameModule(string ModuleName, string MacroName, bool bEnable)
    {
        this.ModuleName = ModuleName;
        this.MacroName = MacroName;

        this.bEnable = bEnable;
    }

    public string ModuleName;
    public string MacroName;

    public bool bEnable;
}

public class UnLuaGame : ModuleRules
{
    [ConfigFile(ConfigHierarchyType.Game, "/Script/UnLuaGame.UnLuaGameSettings", "bExportLuaCJsonLib")]
    bool bExportLuaCJsonLib = false;

    [ConfigFile(ConfigHierarchyType.Game, "/Script/UnLuaGame.UnLuaGameSettings", "bExportLuaProtobufLib")]
    bool bExportLuaProtobufLib = false;

    [ConfigFile(ConfigHierarchyType.Game, "/Script/UnLuaGame.UnLuaGameSettings", "bExportLuaSocketLib")]
    bool bExportLuaSocketLib = false;

    [ConfigFile(ConfigHierarchyType.Game, "/Script/UnLuaGame.UnLuaGameSettings", "bExportLuaPandaLib")]
    bool bExportLuaPandaLib = false;

    [ConfigFile(ConfigHierarchyType.Game, "/Script/UnLuaGame.UnLuaGameSettings", "bExportGameplayAbilitiesLib")]
    bool bExportGameplayAbilitiesLib = false;

    [ConfigFile(ConfigHierarchyType.Game, "/Script/UnLuaGame.UnLuaGameSettings", "bExportHexNavSystemLib")]
    bool bExportHexNavSystemLib = false;

    [ConfigFile(ConfigHierarchyType.Game, "/Script/UnLuaGame.UnLuaGameSettings", "bExportEnhancedInputLib")]
    bool bExportEnhancedInputLib = false;

    public UnLuaGame(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        OptimizeCode = CodeOptimization.InShippingBuildsOnly;

        ConfigCache.ReadSettings(DirectoryReference.FromFile(Target.ProjectFile), Target.Platform, this);

        PublicIncludePaths.AddRange(
            new string[] {

            }
        );


        PrivateIncludePaths.AddRange(
            new string[] {

            }
        );


        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "CoreUObject",
                "Engine",
                "SlateCore",
                "InputCore",
                "RenderCore",
                "AIModule",
                "Lua",
                "UnLua",
                "UMG",
                "HTTP",
                "Sockets",
                "Networking",
                "OnlineSubsystem",
            }
        );


        PrivateDependencyModuleNames.AddRange(
            new string[]
            {

            }
        );


        DynamicallyLoadedModuleNames.AddRange(
            new string[]
            {

            }
        );

        System.Console.WriteLine("-------------------- UnLuaGame Config ----------------------");
        List<UnLuaGameModule> Modules = new List<UnLuaGameModule>();
        Modules.Add(new UnLuaGameModule("LuaCJson", "EXPORT_UNLUA_LUACJSON", bExportLuaCJsonLib));
        Modules.Add(new UnLuaGameModule("LuaProtobuf", "EXPORT_UNLUA_LUAPROTOBUF", bExportLuaProtobufLib));
        Modules.Add(new UnLuaGameModule("LuaSocket", "EXPORT_UNLUA_LUASOCKET", bExportLuaSocketLib));
        Modules.Add(new UnLuaGameModule("LuaPanda", "EXPORT_UNLUA_LUAPANDA", bExportLuaPandaLib));
        Modules.Add(new UnLuaGameModule("UnLuaGameplayAbilities", "EXPORT_UNLUA_GAMEPLAYABILITIES", bExportGameplayAbilitiesLib));
        Modules.Add(new UnLuaGameModule("UnLuaHexNavSystem", "EXPORT_UNLUA_HEXNAVSYSTEM", bExportHexNavSystemLib));
        Modules.Add(new UnLuaGameModule("UnLuaEnhancedInput", "EXPORT_UNLUA_ENHANCEDINPUT", bExportEnhancedInputLib));

        foreach (UnLuaGameModule Module in Modules)
        {
            if (Module.bEnable)
            {
                DynamicallyLoadedModuleNames.Add(Module.ModuleName);
            }
            PublicDefinitions.Add(string.Format("{0} = {1}", Module.MacroName, (Module.bEnable ? "1" : "0")));

            System.Console.WriteLine(string.Format("{0} enable is {1}", Module.ModuleName, Module.bEnable));
        }
        System.Console.WriteLine("---------------------------------------------------------------");
    }
}
