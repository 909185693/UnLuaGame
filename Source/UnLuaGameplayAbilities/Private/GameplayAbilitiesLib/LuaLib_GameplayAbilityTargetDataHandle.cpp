// Copyright 2022 CQUnreal. All Rights Reserved.

#include "UnLuaEx.h"
#include "LuaCore.h"
#include "LuaDynamicBinding.h"
#include "Abilities/GameplayAbilityTargetTypes.h"

static int32 FGameplayAbilityTargetDataHandle_Get(lua_State* L)
{
	int32 NumParams = lua_gettop(L);
	if (NumParams != 2)
	{
		return luaL_error(L, "invalid parameters");
	}

	FGameplayAbilityTargetDataHandle* Handle = (FGameplayAbilityTargetDataHandle*)GetCppInstanceFast(L, 1);
	if (!Handle)
	{
		return luaL_error(L, "invalid FGameplayAbilityTargetDataHandle");
	}

	int32 Index = lua_tointeger(L, 2);
	if (Index <= 0)
	{
		return luaL_error(L, "invalid index '%d'", Index);
	}

	FGameplayAbilityTargetData* NewTargetData = Handle->Get(Index - 1);
	if (!NewTargetData)
	{
		lua_pushnil(L);
		return 1;
	}

	UnLua::Push(L, NewTargetData);
	return 1;
}

static const luaL_Reg FGameplayAbilityTargetDataHandleLib[] =
{
	{ "Get", FGameplayAbilityTargetDataHandle_Get },
	{ nullptr, nullptr }
};

BEGIN_EXPORT_REFLECTED_CLASS(FGameplayAbilityTargetDataHandle)
	ADD_FUNCTION(Clear)
	ADD_FUNCTION(Num)
	ADD_FUNCTION(IsValid)
	ADD_FUNCTION_EX("__eq", bool, operator==, FGameplayAbilityTargetDataHandle const&)
	ADD_LIB(FGameplayAbilityTargetDataHandleLib)
END_EXPORT_CLASS()
IMPLEMENT_EXPORTED_CLASS(FGameplayAbilityTargetDataHandle)
