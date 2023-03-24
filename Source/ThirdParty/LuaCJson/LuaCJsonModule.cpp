// Copyright 2022 CQUnreal. All Rights Reserved.

#include "LuaCJsonModule.h"
#include "lua.hpp"
#include "lua_cjson.h"


IMPLEMENT_MODULE(FLuaCJsonModule, LuaCJson);

void FLuaCJsonModule::RegisterLuaLib(lua_State* L)
{
	//luaopen_cjson(L);
	luaopen_cjson_safe(L);
}

void FLuaCJsonModule::UnRegisterLuaLib(lua_State* L)
{
	
}