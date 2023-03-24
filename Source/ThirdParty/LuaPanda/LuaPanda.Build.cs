// Copyright 2022 CQUnreal. All Rights Reserved.

using System.IO;
using UnrealBuildTool;

public class LuaPanda : ModuleRules
{
	public LuaPanda(ReadOnlyTargetRules Target) : base(Target)
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

#if UE_4_24_OR_LATER
		ShadowVariableWarningLevel = WarningLevel.Off;
        bEnableUndefinedIdentifierWarnings = false;
#else
        bEnableShadowVariableWarnings = false;
        bEnableUndefinedIdentifierWarnings = false;
#endif

        PublicDefinitions.Add("WITH_LUAPANDA=1");
		PrivateDefinitions.Add("USE_SOURCE_CODE");
	}
}
