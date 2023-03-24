// Copyright 2022 CQUnreal. All Rights Reserved.

#include "LuaSocketModule.h"
#include "lua.hpp"
#include "luasocket.h"
#include "mime.h"


IMPLEMENT_MODULE(FLuaSocketModule, LuaSocket);

void FLuaSocketModule::RegisterLuaLib(lua_State* L)
{
	//luaL_getsubtable(L, LUA_REGISTRYINDEX, LUA_PRELOAD_TABLE);

	//lua_pushcfunction(L, luaopen_socket_core);
	//lua_setfield(L, -2, "socket.core");
	luaL_requiref(L, "socket.core", luaopen_socket_core, 1);

	//lua_pushcfunction(L, luaopen_mime_core);
	//lua_setfield(L, -2, "mime.core");
	luaL_requiref(L, "mime.core", luaopen_mime_core, 1);

	/*lua_pushcfunction(L, &FLuaSocketModule::OpenLuaSocketSocket);
	lua_setfield(L, -2, "socket");*/
	luaL_requiref(L, "socket", &FLuaSocketModule::OpenLuaSocketSocket, 1);

	//lua_pushcfunction(L, &FLuaSocketModule::OpenLuaSocketLtn12);
	//lua_setfield(L, -2, "ltn12");
	luaL_requiref(L, "ltn12", &FLuaSocketModule::OpenLuaSocketLtn12, 1);

	//lua_pushcfunction(L, &FLuaSocketModule::OpenLuaSocketMbox);
	//lua_setfield(L, -2, "mbox");
	luaL_requiref(L, "mbox", &FLuaSocketModule::OpenLuaSocketMbox, 1);

	//lua_pushcfunction(L, &FLuaSocketModule::OpenLuaSocketMime);
	//lua_setfield(L, -2, "mime");
	luaL_requiref(L, "mime", &FLuaSocketModule::OpenLuaSocketMime, 1);

	//lua_pushcfunction(L, &FLuaSocketModule::OpenLuaSocketTp);
	//lua_setfield(L, -2, "socket.tp");
	luaL_requiref(L, "socket.tp", &FLuaSocketModule::OpenLuaSocketTp, 1);

	//lua_pushcfunction(L, &FLuaSocketModule::OpenLuaSocketUrl);
	//lua_setfield(L, -2, "socket.url");
	luaL_requiref(L, "socket.url", &FLuaSocketModule::OpenLuaSocketUrl, 1);

	//lua_pushcfunction(L, &FLuaSocketModule::OpenLuaSocketFtp);
	//lua_setfield(L, -2, "socket.ftp");
	luaL_requiref(L, "socket.ftp", &FLuaSocketModule::OpenLuaSocketFtp, 1);

	//lua_pushcfunction(L, &FLuaSocketModule::OpenLuaSocketHeaders);
	//lua_setfield(L, -2, "socket.headers");
	luaL_requiref(L, "socket.headers", &FLuaSocketModule::OpenLuaSocketHeaders, 1);

	//lua_pushcfunction(L, &FLuaSocketModule::OpenLuaSocketHttp);
	//lua_setfield(L, -2, "socket.http");
	luaL_requiref(L, "socket.http", &FLuaSocketModule::OpenLuaSocketHttp, 1);

	//lua_pushcfunction(L, &FLuaSocketModule::OpenLuaSocketSmtp);
	//lua_setfield(L, -2, "socket.smtp");
	luaL_requiref(L, "socket.smtp", &FLuaSocketModule::OpenLuaSocketSmtp, 1);

	// lua_pop(L, 1);
}

void FLuaSocketModule::UnRegisterLuaLib(lua_State* L)
{
	
}

int FLuaSocketModule::OpenLuaSocketFtp(lua_State* L)
{
	static const auto RawLua =
#include "ftp.lua.inc"

	luaL_dostring(L, RawLua);
	return 1;
}

int FLuaSocketModule::OpenLuaSocketHeaders(lua_State* L)
{
	static const auto RawLua =
#include "headers.lua.inc"

	luaL_dostring(L, RawLua);
	return 1;
}

int FLuaSocketModule::OpenLuaSocketHttp(lua_State* L)
{
	static const auto RawLua =
#include "http.lua.inc"

	luaL_dostring(L, RawLua);
	return 1;
}

int FLuaSocketModule::OpenLuaSocketLtn12(lua_State* L)
{
	static const auto RawLua =
#include "ltn12.lua.inc"

	luaL_dostring(L, RawLua);
	return 1;
}

int FLuaSocketModule::OpenLuaSocketMbox(lua_State* L)
{
	static const auto RawLua =
#include "mbox.lua.inc"

	luaL_dostring(L, RawLua);
	return 1;
}

int FLuaSocketModule::OpenLuaSocketMime(lua_State* L)
{
	static const auto RawLua =
#include "mime.lua.inc"

	luaL_dostring(L, RawLua);
	return 1;
}

int FLuaSocketModule::OpenLuaSocketSmtp(lua_State* L)
{
	static const auto RawLua =
#include "smtp.lua.inc"

	luaL_dostring(L, RawLua);
	return 1;
}

int FLuaSocketModule::OpenLuaSocketSocket(lua_State* L)
{
	static const auto RawLua =
#include "socket.lua.inc"

	luaL_dostring(L, RawLua);
	return 1;
}

int FLuaSocketModule::OpenLuaSocketTp(lua_State* L)
{
	static const auto RawLua =
#include "tp.lua.inc"

	luaL_dostring(L, RawLua);
	return 1;
}

int FLuaSocketModule::OpenLuaSocketUrl(lua_State* L)
{
	static const auto RawLua =
#include "url.lua.inc"

	luaL_dostring(L, RawLua);
	return 1;
}
