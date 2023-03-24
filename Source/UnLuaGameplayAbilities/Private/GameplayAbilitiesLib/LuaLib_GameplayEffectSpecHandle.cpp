// Copyright 2022 CQUnreal. All Rights Reserved.

#include "UnLuaEx.h"
#include "LuaCore.h"
#include "LuaDynamicBinding.h"
#include "GameplayEffectTypes.h"

static int32 FGameplayEffectSpecHandle_Get(lua_State* L)
{
	int32 NumParams = lua_gettop(L);
	if (NumParams != 1)
	{
		return luaL_error(L, "invalid parameters");
	}

	FGameplayEffectSpecHandle* EffectSpecHandle = (FGameplayEffectSpecHandle*)GetCppInstanceFast(L, 1);
	if (!EffectSpecHandle)
	{
		return luaL_error(L, "invalid FGameplayEffectSpecHandle");
	}

	if (EffectSpecHandle->IsValid())
	{
		UnLua::Push(L, EffectSpecHandle->Data.Get());
		return 1;
	}

	return 0;
}

static const luaL_Reg FGameplayEffectSpecHandleLib[] =
{
	{ "Get", FGameplayEffectSpecHandle_Get },
	{ nullptr, nullptr }
};

BEGIN_EXPORT_REFLECTED_CLASS(FGameplayEffectSpecHandle)
	ADD_FUNCTION(Clear)
	ADD_FUNCTION(IsValid)
	ADD_FUNCTION_EX("__eq", bool, operator==, FGameplayEffectSpecHandle const&)
	ADD_LIB(FGameplayEffectSpecHandleLib)
END_EXPORT_CLASS()
IMPLEMENT_EXPORTED_CLASS(FGameplayEffectSpecHandle)
