// Copyright 2022 CQUnreal. All Rights Reserved.

#include "UnLuaEx.h"
#include "LuaCore.h"
#include "LuaDynamicBinding.h"
#include "GameFramework/PlayerState.h"
#include "GameFramework/PlayerController.h"

static int32 APlayerController_GetRotationInput(lua_State *L)
{
	int32 NumParams = lua_gettop(L);
	if (NumParams != 1)
	{
		return luaL_error(L, "invalid parameters");
	}

	APlayerController* PlayerController = Cast<APlayerController>(UnLua::GetUObject(L, 1));
	if (!PlayerController)
	{
		return luaL_error(L, "invalid APlayerController");
	}

	void *Userdata = NewTypedUserdata(L, FRotator);
	new(Userdata) FRotator(PlayerController->RotationInput);
	return 1;
}

static int32 APlayerController_GetUniqueNetId(lua_State* L)
{
	int32 NumParams = lua_gettop(L);
	if (NumParams != 1)
	{
		return luaL_error(L, "invalid parameters");
	}

	APlayerController* PlayerController = Cast<APlayerController>(UnLua::GetUObject(L, 1));
	if (!PlayerController)
	{
		return luaL_error(L, "invalid APlayerController");
	}

	void* Userdata = NewTypedUserdata(L, FUniqueNetIdRepl);
	FUniqueNetIdRepl* UniqueNetIdRepl = new(Userdata) FUniqueNetIdRepl();

	APlayerState* PlayerState = PlayerController->GetPlayerState<APlayerState>();
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

static const luaL_Reg APlayerControllerLib[] =
{
	{ "GetRotationInput", APlayerController_GetRotationInput },
	{ "GetUniqueNetId", APlayerController_GetUniqueNetId },
    { nullptr, nullptr }
};

BEGIN_EXPORT_REFLECTED_CLASS(APlayerController)
	ADD_FUNCTION(StartTalking)
	ADD_FUNCTION(StopTalking)
	ADD_FUNCTION(GameplayMutePlayer)
	ADD_FUNCTION(GameplayUnmutePlayer)
	ADD_FUNCTION(GetPlayerViewPoint)
	ADD_LIB(APlayerControllerLib)
END_EXPORT_CLASS()
IMPLEMENT_EXPORTED_CLASS(APlayerController)
