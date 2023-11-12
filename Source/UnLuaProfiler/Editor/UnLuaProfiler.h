// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Runtime/Launch/Resources/Version.h"
#if (ENGINE_MAJOR_VERSION >= 4 && ENGINE_MINOR_VERSION >= 20) || ENGINE_MAJOR_VERSION >= 5
#include "Modules/ModuleManager.h"
#else
#include "ModuleManager.h"
#endif

#include "UnLuaProfilerBase.h"
#include "UnLuaMonitor/UnLuaMonitorPanel.h"
#include "UnLuaMemAnalyzer/UnLuaMemAnalyzerPanel.h"
#include "Widgets/Docking/SDockTab.h"
#include "Misc/EngineVersionComparison.h"

/** Declares a log category for this module. */
DECLARE_LOG_CATEGORY_EXTERN(LogUnLuaProfiler, Log, All);

#ifdef ENABLE_UNLUAPROFILER
#endif

class FUnLuaProfilerModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
    
	void OnClickedOpenMonitorPanel();

	void OnClickedOpenMemAnalyzerPanel();

private:
	TSharedRef<class SDockTab> OnSpawnUnLuaMonitorTab(const class FSpawnTabArgs& SpawnTabArgs);
	TSharedRef<class SDockTab> OnSpawnUnLuaMemAnalyzerTab(const class FSpawnTabArgs& SpawnTabArgs);
	bool Tick(float DeltaTime);
	void AddMenuExtension(FMenuBuilder& Builder);
	void AddProfilerMenu(FMenuBuilder& Builder);

private:
	FTickerDelegate TickDelegate;
#if UE_VERSION_OLDER_THAN(5, 3, 0)
	FDelegateHandle TickDelegateHandle;
#else
	FTSTicker::FDelegateHandle TickDelegateHandle;
#endif
	TSharedPtr<class FUICommandList> PluginCommands;
	TSharedPtr<SUnLuaMonitorPanel> MonitorPanel;
	TSharedPtr<SUnLuaMemAnalyzerPanel> MemAnalyzerPanel;
};
