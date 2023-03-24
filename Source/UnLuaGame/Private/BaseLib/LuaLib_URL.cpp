// Copyright 2022 CQUnreal. All Rights Reserved.

#include "UnLuaEx.h"
#include "LuaCore.h"
#include "Engine/EngineBaseTypes.h"


static int32 FURL_New(lua_State *L)
{
	void *Userdata = NewTypedUserdata(L, FKey);
	new(Userdata) FURL();

	return 1;
}

static int32 FURL_HasOption(lua_State* L)
{
	int32 NumParams = lua_gettop(L);
	if (NumParams != 2)
	{
		return luaL_error(L, "invalid parameters");
	}

	FURL* URL = (FURL*)GetCppInstanceFast(L, 1);
	if (!URL)
	{
		return luaL_error(L, "invalid FURL");
	}

	const char* Test = lua_tostring(L, 2);
	if (!Test)
	{
		return luaL_error(L, "invalid parameters");
	}

	lua_pushboolean(L, URL->HasOption(UTF8_TO_TCHAR(Test)));
	return 1;
}

static int32 FURL_GetOption(lua_State* L)
{
	int32 NumParams = lua_gettop(L);
	if (NumParams < 2)
	{
		return luaL_error(L, "invalid parameters");
	}

	FURL* URL = (FURL*)GetCppInstanceFast(L, 1);
	if (!URL)
	{
		return luaL_error(L, "invalid FURL");
	}

	const char* Match = lua_tostring(L, 2);
	if (!Match)
	{
		return luaL_error(L, "invalid parameters");
	}

	const char* Default = lua_tostring(L, 3);
	if (!Default)
	{
		Default = "";
	}

	lua_pushstring(L, TCHAR_TO_UTF8(URL->GetOption(UTF8_TO_TCHAR(Match), UTF8_TO_TCHAR(Default))));
	return 1;
}

static int32 FURL_AddOption(lua_State* L)
{
	int32 NumParams = lua_gettop(L);
	if (NumParams != 2)
	{
		return luaL_error(L, "invalid parameters");
	}

	FURL* URL = (FURL*)GetCppInstanceFast(L, 1);
	if (!URL)
	{
		return luaL_error(L, "invalid FURL");
	}

	const char* Str = lua_tostring(L, 2);
	if (!Str)
	{
		return luaL_error(L, "invalid parameters");
	}

	URL->AddOption(UTF8_TO_TCHAR(Str));
	return 0;
}

static int32 FURL_RemoveOption(lua_State* L)
{
	int32 NumParams = lua_gettop(L);
	if (NumParams < 2)
	{
		return luaL_error(L, "invalid parameters");
	}

	FURL* URL = (FURL*)GetCppInstanceFast(L, 1);
	if (!URL)
	{
		return luaL_error(L, "invalid FURL");
	}

	const char* Key = lua_tostring(L, 2);
	if (!Key)
	{
		return luaL_error(L, "invalid parameters");
	}

	const char* Section = lua_tostring(L, 3);
	if (!Section)
	{
		return luaL_error(L, "invalid parameters");
	}

	const char* Filename = lua_tostring(L, 4);
	if (Filename)
	{
		URL->RemoveOption(UTF8_TO_TCHAR(Key), UTF8_TO_TCHAR(Section));
	}
	else
	{
		URL->RemoveOption(UTF8_TO_TCHAR(Key), UTF8_TO_TCHAR(Section), UTF8_TO_TCHAR(Filename));
	}

	return 0;
}

static int32 FURL_GetPort(lua_State* L)
{
	int32 NumParams = lua_gettop(L);
	if (NumParams != 1)
	{
		return luaL_error(L, "invalid parameters");
	}

	FURL* URL = (FURL*)GetCppInstanceFast(L, 1);
	if (!URL)
	{
		return luaL_error(L, "invalid FURL");
	}

	lua_pushnumber(L, URL->Port);
	return 1;
}

static int32 FURL_GetProtocol(lua_State* L)
{
	int32 NumParams = lua_gettop(L);
	if (NumParams != 1)
	{
		return luaL_error(L, "invalid parameters");
	}

	FURL* URL = (FURL*)GetCppInstanceFast(L, 1);
	if (!URL)
	{
		return luaL_error(L, "invalid FURL");
	}

	lua_pushstring(L, TCHAR_TO_UTF8(*URL->Protocol));
	return 1;
}

static int32 FURL_GetHost(lua_State* L)
{
	int32 NumParams = lua_gettop(L);
	if (NumParams != 1)
	{
		return luaL_error(L, "invalid parameters");
	}

	FURL* URL = (FURL*)GetCppInstanceFast(L, 1);
	if (!URL)
	{
		return luaL_error(L, "invalid FURL");
	}

	lua_pushstring(L, TCHAR_TO_UTF8(*URL->Host));
	return 1;
}

static int32 FURL_IsValid(lua_State* L)
{
	int32 NumParams = lua_gettop(L);
	if (NumParams != 1)
	{
		return luaL_error(L, "invalid parameters");
	}

	FURL* URL = (FURL*)GetCppInstanceFast(L, 1);
	if (!URL)
	{
		return luaL_error(L, "invalid FURL");
	}

	lua_pushboolean(L, !!URL->Valid);
	return 1;
}

static int32 FURL_GetMap(lua_State* L)
{
	int32 NumParams = lua_gettop(L);
	if (NumParams != 1)
	{
		return luaL_error(L, "invalid parameters");
	}

	FURL* URL = (FURL*)GetCppInstanceFast(L, 1);
	if (!URL)
	{
		return luaL_error(L, "invalid FURL");
	}

	lua_pushstring(L, TCHAR_TO_UTF8(*URL->Map));
	return 1;
}

static int32 FURL_GetRedirectURL(lua_State* L)
{
	int32 NumParams = lua_gettop(L);
	if (NumParams != 1)
	{
		return luaL_error(L, "invalid parameters");
	}

	FURL* URL = (FURL*)GetCppInstanceFast(L, 1);
	if (!URL)
	{
		return luaL_error(L, "invalid FURL");
	}

	lua_pushstring(L, TCHAR_TO_UTF8(*URL->RedirectURL));
	return 1;
}

static int32 FURL_GetOp(lua_State* L)
{
	int32 NumParams = lua_gettop(L);
	if (NumParams != 1)
	{
		return luaL_error(L, "invalid parameters");
	}

	FURL* URL = (FURL*)GetCppInstanceFast(L, 1);
	if (!URL)
	{
		return luaL_error(L, "invalid FURL");
	}

	auto& Env = UnLua::FLuaEnv::FindEnvChecked(L);
	TSharedPtr<UnLua::ITypeInterface> TypeInterface = Env.GetPropertyRegistry()->GetStringProperty();

	UnLua::PushArray(L, (FScriptArray*)&URL->Op, TypeInterface);

	return 1;
}

static int32 FURL_GetPortal(lua_State* L)
{
	int32 NumParams = lua_gettop(L);
	if (NumParams != 1)
	{
		return luaL_error(L, "invalid parameters");
	}

	FURL* URL = (FURL*)GetCppInstanceFast(L, 1);
	if (!URL)
	{
		return luaL_error(L, "invalid FURL");
	}

	lua_pushstring(L, TCHAR_TO_UTF8(*URL->Portal));
	return 1;
}

static const luaL_Reg FURLLib[] =
{
	{ "__call", FURL_New },
	{ "HasOption", FURL_HasOption },
	{ "GetOption", FURL_GetOption },
	{ "AddOption", FURL_AddOption },
	{ "RemoveOption", FURL_RemoveOption },
	{ "GetPort", FURL_GetPort },
	{ "GetProtocol", FURL_GetProtocol },
	{ "GetHost", FURL_GetHost },
	{ "IsValid", FURL_IsValid },
	{ "GetHost", FURL_GetHost },
	{ "GetMap", FURL_GetMap },
	{ "GetRedirectURL", FURL_GetRedirectURL },
	{ "GetOp", FURL_GetOp },
	{ "GetPortal", FURL_GetPortal },
	{ nullptr, nullptr }
};

BEGIN_EXPORT_REFLECTED_CLASS(FURL)
	ADD_FUNCTION(LoadURLConfig)
	ADD_FUNCTION(SaveURLConfig)
	ADD_FUNCTION(AddOption)
	ADD_FUNCTION(RemoveOption)
	ADD_FUNCTION(GetHostPortString)
	ADD_FUNCTION(IsInternal)
	ADD_FUNCTION(IsLocalInternal)
	ADD_LIB(FURLLib)
END_EXPORT_CLASS()
IMPLEMENT_EXPORTED_CLASS(FURL)
