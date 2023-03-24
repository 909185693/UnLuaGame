// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "UnLuaProfilerCommands.h"
#include "UnLuaProfilerBase.h"
#if WITH_EDITOR
#include "EditorStyleSet.h"
#endif

#define LOCTEXT_NAMESPACE "FUnLuaProfilerModule"

#if WITH_EDITOR
using namespace UnLuaProfiler;

FUnLuaProfilerCommands::FUnLuaProfilerCommands()
	: TCommands<FUnLuaProfilerCommands>(UnLuaProfiler::UnLuaMonitorTabName,
		NSLOCTEXT("Contexts", "LuaProfiler", "LuaProfiler Plugin"), NAME_None, FEditorStyle::GetStyleSetName())
{

}

void FUnLuaProfilerCommands::RegisterCommands()
{
	UI_COMMAND(OpenMonitorPanel, "UnLuaMonitor", "Open UnLuaMonitor", EUserInterfaceActionType::Button, FInputChord());
	UI_COMMAND(OpenMemAnalyzerPanel, "UnLuaMemAnalyzer", "Open UnLuaMemAnalyzer", EUserInterfaceActionType::Button, FInputChord());
}

#endif

#undef LOCTEXT_NAMESPACE
