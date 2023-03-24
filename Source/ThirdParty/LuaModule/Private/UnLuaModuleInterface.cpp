// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.


#include "UnLuaModuleInterface.h"

void IUnLuaModuleInterface::StartupModule()
{
	LuaEnvCreatedHandle = UnLua::FLuaEnv::OnCreated.AddRaw(this, &IUnLuaModuleInterface::OnLuaEnvCreated);
}

void IUnLuaModuleInterface::ShutdownModule()
{
	UnLua::FLuaEnv::OnCreated.Remove(LuaEnvCreatedHandle);
}

void IUnLuaModuleInterface::OnLuaEnvCreated(UnLua::FLuaEnv& LuaEnv)
{
	lua_State* L = LuaEnv.GetMainState();

	RegisterLuaLib(L);
}