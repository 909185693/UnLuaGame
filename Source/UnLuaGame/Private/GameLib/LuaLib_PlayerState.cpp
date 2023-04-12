// Copyright 2022 CQUnreal. All Rights Reserved.

#include "UnLuaEx.h"
#include "LuaCore.h"
#include "LuaDynamicBinding.h"
#include "GameFramework/PlayerState.h"

static int32 APlayerState_GetUniqueNetId(lua_State* L)
{
	int32 NumParams = lua_gettop(L);
	if (NumParams != 1)
	{
		return luaL_error(L, "invalid parameters");
	}

	APlayerState* PlayerState = Cast<APlayerState>(UnLua::GetUObject(L, 1));
	if (!PlayerState)
	{
		return luaL_error(L, "invalid APlayerState");
	}

	void* Userdata = NewTypedUserdata(L, FUniqueNetIdRepl);
	FUniqueNetIdRepl* UniqueNetIdRepl = new(Userdata) FUniqueNetIdRepl();

	if (PlayerState != nullptr)
	{
#if ENGINE_MAJOR_VERSION > 4 || ENGINE_MINOR_VERSION > 24
		*UniqueNetIdRepl = PlayerState->GetUniqueId();
#else
		*UniqueNetIdRepl = PlayerState->UniqueId;
#endif
	}

	return 1;
}

static const luaL_Reg APlayerStateLib[] =
{
	{ "GetUniqueNetId", APlayerState_GetUniqueNetId },
    { nullptr, nullptr }
};

BEGIN_EXPORT_REFLECTED_CLASS(APlayerState)
	ADD_FUNCTION(SetPlayerName)
#if ENGINE_MAJOR_VERSION >= 5
	ADD_FUNCTION(GetPingInMilliseconds)
	ADD_FUNCTION(GetCompressedPing)
#else
	ADD_FUNCTION(GetPing)
#endif
    ADD_LIB(APlayerStateLib)
END_EXPORT_CLASS()
IMPLEMENT_EXPORTED_CLASS(APlayerState)
