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

	TArray<uint8> Data;

	if (PlayerState != nullptr)
	{
#if ENGINE_MAJOR_VERSION > 4 || ENGINE_MINOR_VERSION > 24
		FUniqueNetIdRepl UniqueNetId = PlayerState->GetUniqueId();
#else
		FUniqueNetIdRepl UniqueNetId = PlayerState->UniqueId;
#endif
		if (UniqueNetId.IsValid())
		{
			int32 Size = UniqueNetId->GetSize();

			Data.Reset();
			Data.AddUninitialized(Size);

			FMemory::Memcpy(Data.GetData(), UniqueNetId->GetBytes(), Size);
		}
	}

	lua_pushstring(L, (const char*)Data.GetData());
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
