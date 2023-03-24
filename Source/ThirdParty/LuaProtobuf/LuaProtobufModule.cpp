// Copyright 2022 CQUnreal. All Rights Reserved.

#include "LuaProtobufModule.h"
#include "lua.hpp"
#include "pb.h"
#include "serpent_lua.h"
#include "protoc_lua.h"


IMPLEMENT_MODULE(FLuaProtobufModule, LuaProtobuf);

int OpenProtoc(lua_State* L)
{
	luaL_dostring(L, (const char*)protoc_lua_data);
	return 1;
}

int OpenSerpent(lua_State* L)
{
	luaL_dostring(L, (const char*)serpent_lua_data);
	return 1;
}

void FLuaProtobufModule::RegisterLuaLib(lua_State* L)
{
	luaL_requiref(L, "pb", luaopen_pb, 0);
	luaL_requiref(L, "pb.slice", luaopen_pb_slice, 0);
	luaL_requiref(L, "pb.buffer", luaopen_pb_buffer, 0);
	luaL_requiref(L, "pb.conv", luaopen_pb_conv, 0);
	luaL_requiref(L, "protoc", &::OpenProtoc, 1);
	luaL_requiref(L, "serpent", &::OpenSerpent, 1);
}

void FLuaProtobufModule::UnRegisterLuaLib(lua_State* L)
{
	
}
