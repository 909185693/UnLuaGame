// Copyright 2022 CQUnreal. All Rights Reserved.

using System.IO;
using UnrealBuildTool;

public class LuaCJson : ModuleRules
{
	public LuaCJson(ReadOnlyTargetRules Target) : base(Target)
	{
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        bUseUnity = false;
#if UE_5_2_OR_LATER
        IWYUSupport = IWYUSupport.None;
#else
        bEnforceIWYU = false;
#endif

        PublicDependencyModuleNames.AddRange(new string[] { "Core" });

		PrivateDependencyModuleNames.AddRange(new string[] { "Lua", "LuaModule" });

        PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "src"));

        PrivateDefinitions.Add("ENABLE_CJSON_GLOBAL=1");

#if UE_4_24_OR_LATER
		ShadowVariableWarningLevel = WarningLevel.Off;
        bEnableUndefinedIdentifierWarnings = false;
#else
        bEnableShadowVariableWarnings = false;
        bEnableUndefinedIdentifierWarnings = false;
#endif

    }
}
