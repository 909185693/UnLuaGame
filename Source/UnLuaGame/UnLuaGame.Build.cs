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

public class UnLuaGame : ModuleRules
{
    public UnLuaGame(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        OptimizeCode = CodeOptimization.InShippingBuildsOnly;

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

        var ProjectDir = Target.ProjectFile.Directory;
        var ConfigFilePath = ProjectDir + "/Config/DefaultUnLuaGame.ini";
        var ConfigFileReference = new FileReference(ConfigFilePath);
        var ConfigFile = FileReference.Exists(ConfigFileReference) ? new ConfigFile(ConfigFileReference) : new ConfigFile();
        var Config = new ConfigHierarchy(new[] { ConfigFile });
        const string Section = "/Script/UnLuaGame.UnLuaGameSettings";

        Action<string, string, string[]> LoadModuleFromConfig = (FieldName, MacroName, DependencyModuleNames) =>
        {
            bool bFlag = false;
            Config.GetBool(Section, FieldName, out bFlag);

            PublicDefinitions.Add(string.Format("{0} = {1}", MacroName, (bFlag ? "1" : "0")));
            if (bFlag)
            {
                DynamicallyLoadedModuleNames.AddRange(DependencyModuleNames);
            }

            System.Console.WriteLine(string.Format("{0} = {1}", FieldName, bFlag));
        };

        System.Console.WriteLine("-------------------- UnLuaGame Config ----------------------");
        LoadModuleFromConfig("bExportLuaCJsonLib", "EXPORT_UNLUA_LUACJSON", new string[] { "LuaCJson" });
        LoadModuleFromConfig("bExportLuaProtobufLib", "EXPORT_UNLUA_LUAPROTOBUF", new string[] { "LuaProtobuf" });
        LoadModuleFromConfig("bExportLuaSocketLib", "EXPORT_UNLUA_LUASOCKET", new string[] { "LuaSocket" });
        LoadModuleFromConfig("bExportLuaPandaLib", "EXPORT_UNLUA_LUAPANDA", new string[] { "LuaPanda" });
        LoadModuleFromConfig("bExportGameplayAbilitiesLib", "EXPORT_UNLUA_GAMEPLAYABILITIES", new string[] { "UnLuaGameplayAbilities" });
        LoadModuleFromConfig("bExportHexNavSystemLib", "EXPORT_UNLUA_HEXNAVSYSTEM", new string[] { "UnLuaHexNavSystem" });
        LoadModuleFromConfig("bExportEnhancedInputLib", "EXPORT_UNLUA_ENHANCEDINPUT", new string[] { "UnLuaEnhancedInput" });
        System.Console.WriteLine("---------------------------------------------------------------");
    }
}
