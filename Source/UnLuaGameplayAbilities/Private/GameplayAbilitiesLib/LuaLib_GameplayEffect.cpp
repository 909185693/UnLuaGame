// Copyright 2022 CQUnreal. All Rights Reserved.

#include "UnLuaEx.h"
#include "LuaCore.h"
#include "LuaDynamicBinding.h"
#include "GameplayEffect.h"

static const luaL_Reg UGameplayEffectLib[] =
{
	{ nullptr, nullptr }
};

BEGIN_EXPORT_REFLECTED_CLASS(UGameplayEffect)
	ADD_FUNCTION(GetAssetTags)
	ADD_FUNCTION(GetGrantedTags)
	ADD_CONST_FUNCTION_EX("GetBlockedAbilityTags", const FGameplayTagContainer&, GetBlockedAbilityTags)
	ADD_LIB(UGameplayEffectLib)
END_EXPORT_CLASS()
IMPLEMENT_EXPORTED_CLASS(UGameplayEffect)
