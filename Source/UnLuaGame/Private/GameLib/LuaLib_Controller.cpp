// Copyright 2022 CQUnreal. All Rights Reserved.

#include "UnLuaEx.h"
#include "LuaCore.h"
#include "LuaDynamicBinding.h"
#include "GameFramework/Controller.h"

static int32 AController_GetStartSpot(lua_State *L)
{
	int32 NumParams = lua_gettop(L);
	if (NumParams != 1)
	{
		return luaL_error(L, "invalid parameters");
	}

	AController *Controller = Cast<AController>(UnLua::GetUObject(L, 1));
	if (!Controller)
	{
		UE_LOG(LogUnLua, Log, TEXT("%s: Invalid Controller!"), ANSI_TO_TCHAR(__FUNCTION__));
		lua_pushnil(L);
		return 1;
	}

	UnLua::PushUObject(L, Controller->StartSpot.IsValid() ? Controller->StartSpot.Get() : nullptr);

	return 1;
}

static int32 AController_SetStartSpot(lua_State *L)
{
	int32 NumParams = lua_gettop(L);
	if (NumParams != 2)
	{
		return luaL_error(L, "invalid parameters");
	}

	AController *Controller = Cast<AController>(UnLua::GetUObject(L, 1));
	if (!Controller)
	{
		UE_LOG(LogUnLua, Log, TEXT("%s: Invalid Controller!"), ANSI_TO_TCHAR(__FUNCTION__));
		lua_pushnil(L);
		return 1;
	}

	Controller->StartSpot = Cast<AActor>(UnLua::GetUObject(L, 2));

	return 1;
}

static int32 AController_DestroyController(lua_State *L)
{
	int32 NumParams = lua_gettop(L);
	if (NumParams < 1)
	{
		return luaL_error(L, "invalid parameters");
	}

	AController *Controller = Cast<AController>(UnLua::GetUObject(L, 1));
	if (!Controller)
	{
		return luaL_error(L, "invalid AController");
	}

	bool bNetForce = false;
	if (NumParams > 1)
	{
		bNetForce = (bool)lua_toboolean(L, 2);
	}

	bool bShouldModifyLevel = true;
	if (NumParams > 2)
	{
		bShouldModifyLevel = (bool)lua_toboolean(L, 3);
	}

	Controller->Destroy();
	return 0;
}

static const luaL_Reg AControllerLib[] =
{
	{ "GetStartSpot", AController_GetStartSpot },
	{ "SetStartSpot", AController_SetStartSpot },
	{ "DestroyController", AController_DestroyController },
    { nullptr, nullptr }
};

BEGIN_EXPORT_REFLECTED_CLASS(AController)
    ADD_LIB(AControllerLib)
END_EXPORT_CLASS()
IMPLEMENT_EXPORTED_CLASS(AController)
