// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "UnLuaProfiler.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"
#if WITH_EDITOR
#include "LevelEditor.h"
#include "Styles/UnLuaStyle.h"
#include "Styles/UnLuaProfilerCommands.h"
#endif

DEFINE_LOG_CATEGORY(LogUnLuaProfiler)
#define LOCTEXT_NAMESPACE "FUnLuaProfilerModule"

void FUnLuaProfilerModule::StartupModule()
{
#if WITH_EDITOR

	FUnLuaProfilerCommands::Register();

	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FUnLuaProfilerCommands::Get().OpenMonitorPanel,
		FExecuteAction::CreateRaw(this, &FUnLuaProfilerModule::OnClickedOpenMonitorPanel),
		FCanExecuteAction());

	PluginCommands->MapAction(
		FUnLuaProfilerCommands::Get().OpenMemAnalyzerPanel,
		FExecuteAction::CreateRaw(this, &FUnLuaProfilerModule::OnClickedOpenMemAnalyzerPanel),
		FCanExecuteAction());

	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");

	{
		TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());
		MenuExtender->AddMenuExtension("WindowLayout", EExtensionHook::After, PluginCommands, FMenuExtensionDelegate::CreateRaw(this, &FUnLuaProfilerModule::AddMenuExtension));

		LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
	}


	if (GIsEditor && !IsRunningCommandlet())
	{
		FGlobalTabmanager::Get()->RegisterNomadTabSpawner(UnLuaProfiler::UnLuaMonitorTabName,
			FOnSpawnTab::CreateRaw(this, &FUnLuaProfilerModule::OnSpawnUnLuaMonitorTab))
			.SetDisplayName(LOCTEXT("Flua_wrapperTabTitle", "DONT WORRY BE HAPPY"))
			.SetMenuType(ETabSpawnerMenuType::Hidden);

		FGlobalTabmanager::Get()->RegisterNomadTabSpawner(UnLuaProfiler::UnLuaMemAnalyzerTabName,
			FOnSpawnTab::CreateRaw(this, &FUnLuaProfilerModule::OnSpawnUnLuaMemAnalyzerTab))
			.SetDisplayName(LOCTEXT("Flua_wrapperTabTitle", "DONT WORRY BE HAPPY"))
			.SetMenuType(ETabSpawnerMenuType::Hidden);

		TickDelegate = FTickerDelegate::CreateRaw(this, &FUnLuaProfilerModule::Tick);
		#if UE_VERSION_OLDER_THAN(5, 3, 0)
		TickDelegateHandle = FTicker::GetCoreTicker().AddTicker(TickDelegate);
		#else
		TickDelegateHandle = FTSTicker::GetCoreTicker().AddTicker(TickDelegate);
		#endif
	}

	if (GIsEditor)
	{
		FUnLuaStyle::Initialize();
	}
#endif
}

void FUnLuaProfilerModule::ShutdownModule()
{
#if WITH_EDITOR
	if (MonitorPanel.IsValid())
	{
		MonitorPanel = nullptr;
	}

	if (MemAnalyzerPanel.IsValid())
	{
		MemAnalyzerPanel = nullptr;
	}

	FUnLuaProfilerCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(UnLuaProfiler::UnLuaMonitorTabName);

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(UnLuaProfiler::UnLuaMemAnalyzerTabName);

	if (GIsEditor)
	{
		FUnLuaStyle::Shutdown();
	}
#endif
}

void FUnLuaProfilerModule::OnClickedOpenMonitorPanel()
{
#if ENGINE_MAJOR_VERSION >= 5 || (ENGINE_MAJOR_VERSION == 4 && ENGINE_MINOR_VERSION >= 26)
	FGlobalTabmanager::Get()->TryInvokeTab(UnLuaProfiler::UnLuaMonitorTabName);
#else
	FGlobalTabmanager::Get()->InvokeTab(UnLuaProfiler::UnLuaMonitorTabName);
#endif
}

void FUnLuaProfilerModule::OnClickedOpenMemAnalyzerPanel()
{
#if ENGINE_MAJOR_VERSION >= 5 || (ENGINE_MAJOR_VERSION == 4 && ENGINE_MINOR_VERSION >= 26)
	FGlobalTabmanager::Get()->TryInvokeTab(UnLuaProfiler::UnLuaMemAnalyzerTabName);
#else
	FGlobalTabmanager::Get()->InvokeTab(UnLuaProfiler::UnLuaMemAnalyzerTabName);
#endif
}

bool FUnLuaProfilerModule::Tick(float DeltaTime)
{
	if (MonitorPanel.IsValid() && MonitorPanel->IsOpening())
	{
		MonitorPanel->DeferredTick(DeltaTime);
	}

	if (MemAnalyzerPanel.IsValid() && MemAnalyzerPanel->IsOpening())
	{
		MemAnalyzerPanel->DeferredTick(DeltaTime);
	}

	return true;
}

TSharedRef<class SDockTab> FUnLuaProfilerModule::OnSpawnUnLuaMonitorTab(const FSpawnTabArgs& SpawnTabArgs)
{
	if (!MonitorPanel.IsValid())
	{
		SAssignNew(MonitorPanel, SUnLuaMonitorPanel);
	}
	TSharedRef<SDockTab> DockTab = MonitorPanel->GetSDockTab();
	return DockTab;
}

TSharedRef<class SDockTab> FUnLuaProfilerModule::OnSpawnUnLuaMemAnalyzerTab(const FSpawnTabArgs& SpawnTabArgs)
{
	if (!MemAnalyzerPanel.IsValid())
	{
		SAssignNew(MemAnalyzerPanel, SUnLuaMemAnalyzerPanel);
	}
	TSharedRef<SDockTab> DockTab = MemAnalyzerPanel->GetSDockTab();
	return DockTab;
}

void FUnLuaProfilerModule::AddMenuExtension(FMenuBuilder & Builder)
{
#if WITH_EDITOR
	Builder.BeginSection("UnLuaProfiler", TAttribute<FText>(FText::FromString("UnLuaProfiler")));
	{
		Builder.AddSubMenu(FText::FromString("UnLuaProfiler"),
			FText::FromString("DONT WORRY BE HAPPY"),
			FNewMenuDelegate::CreateRaw(this, &FUnLuaProfilerModule::AddProfilerMenu));
	}
	Builder.EndSection();
#endif
}

void FUnLuaProfilerModule::AddProfilerMenu(FMenuBuilder& Builder)
{
	Builder.BeginSection("UnLuaProfiler", TAttribute<FText>(FText::FromString("UnLuaProfiler")));
	{
		Builder.AddMenuEntry(FUnLuaProfilerCommands::Get().OpenMonitorPanel);

		Builder.AddMenuEntry(FUnLuaProfilerCommands::Get().OpenMemAnalyzerPanel);
	}
	Builder.EndSection();
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FUnLuaProfilerModule, UnLuaProfiler)
