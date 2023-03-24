// Copyright 2022 CQUnreal. All Rights Reserved.

using System.IO;
using UnrealBuildTool;

public class LuaSocket : ModuleRules
{
	public LuaSocket(ReadOnlyTargetRules Target) : base(Target)
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

        PublicDefinitions.Add("WITH_LIBLUASOCKET=1");

        PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "src"));

        if (Target.Configuration == UnrealTargetConfiguration.Debug ||
			Target.Configuration == UnrealTargetConfiguration.DebugGame)
		{
			PrivateDefinitions.Add("LUASOCKET_DEBUG");
        }

#if UE_4_24_OR_LATER
		ShadowVariableWarningLevel = WarningLevel.Off;
        bEnableUndefinedIdentifierWarnings = false;
#else
        bEnableShadowVariableWarnings = false;
        bEnableUndefinedIdentifierWarnings = false;
#endif

#if UE_5_0_OR_LATER
        if (Target.Platform == UnrealTargetPlatform.Win64)
#else
        if (Target.Platform == UnrealTargetPlatform.Win32 || Target.Platform == UnrealTargetPlatform.Win64)
#endif
        {
            PublicDefinitions.Add("_CRT_SECURE_NO_WARNINGS");
        }
    }
}
