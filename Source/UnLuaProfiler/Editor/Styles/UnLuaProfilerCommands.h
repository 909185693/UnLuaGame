// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Framework/Commands/Commands.h"

#if WITH_EDITOR

class FUnLuaProfilerCommands : public TCommands<FUnLuaProfilerCommands>
{
public:
	FUnLuaProfilerCommands();

	virtual void RegisterCommands() override;

public:
	TSharedPtr<FUICommandInfo> OpenMonitorPanel;
	TSharedPtr<FUICommandInfo> OpenMemAnalyzerPanel;
};

#endif
