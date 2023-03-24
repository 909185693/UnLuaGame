// Copyright 2022 CQUnreal. All Rights Reserved.

#include "UnLuaEx.h"
#include "LuaCore.h"
#include "LuaDynamicBinding.h"
#include "Abilities/GameplayAbility.h"

/// <summary>
/// GameplayAbilityLib
/// </summary>

static const luaL_Reg UGameplayAbilityLib[] =
{
    { nullptr, nullptr }
};

BEGIN_EXPORT_REFLECTED_CLASS(UGameplayAbility)
	ADD_FUNCTION(IsActive)
	ADD_FUNCTION(IsTriggered)
	ADD_FUNCTION(IsPredictingClient)
	ADD_FUNCTION(IsForRemoteClient)
	ADD_FUNCTION(IsInstantiated)
	ADD_FUNCTION(CanBeCanceled)
	ADD_FUNCTION(GetCurrentAbilitySpecHandle)
    ADD_LIB(UGameplayAbilityLib)
END_EXPORT_CLASS()
IMPLEMENT_EXPORTED_CLASS(UGameplayAbility)
