// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "lua.hpp"
#include "LuaEnv.h"
#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"


class LUAMODULE_API IUnLuaModuleInterface : public IModuleInterface
{
public:
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	virtual void OnLuaEnvCreated(UnLua::FLuaEnv& LuaEnv);

	virtual void RegisterLuaLib(lua_State* L) = 0;
	virtual void UnRegisterLuaLib(lua_State* L) = 0;

private:
	FDelegateHandle LuaEnvCreatedHandle;
};