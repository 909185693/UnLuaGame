// Copyright 2022 CQUnreal. All Rights Reserved.

#include "LuaPandaModule.h"
#include "lua.hpp"
#include "libpdebug.h"
#include "LuaPanda.inl"


IMPLEMENT_MODULE(FLuaPandaModule, LuaPanda);

int FLuaPandaModule::OpenLuaPanda(lua_State* L)
{
	// UE_LOG(LogTemp, Log, TEXT("Call open lua panda"));
	luaL_dostring(L, (const char*)LuaPanda_lua_data);

	return 1;
}

void FLuaPandaModule::RegisterLuaLib(lua_State* L)
{
	pdebug_init(L);

	//luaL_getsubtable(L, LUA_REGISTRYINDEX, LUA_PRELOAD_TABLE);

	//lua_pushcfunction(L, &FLuaPanda::OpenLuaPanda);
	//lua_setfield(L, -2, "LuaPanda");

	luaL_requiref(L, "LuaPanda", &FLuaPandaModule::OpenLuaPanda, 1);
	// lua_pop(L, 1);
}

void FLuaPandaModule::UnRegisterLuaLib(lua_State* L)
{
	
}
