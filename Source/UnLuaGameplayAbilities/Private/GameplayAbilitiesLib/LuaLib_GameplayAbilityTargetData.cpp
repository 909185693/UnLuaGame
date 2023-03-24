// Copyright 2022 CQUnreal. All Rights Reserved.

#include "UnLuaEx.h"
#include "LuaCore.h"
#include "LuaDynamicBinding.h"
#include "Abilities/GameplayAbilityTargetTypes.h"


BEGIN_EXPORT_REFLECTED_CLASS(FGameplayAbilityTargetData)
	ADD_FUNCTION(ApplyGameplayEffect)
	ADD_FUNCTION(ApplyGameplayEffectSpec)
	ADD_FUNCTION(AddTargetDataToContext)
	ADD_FUNCTION(AddTargetDataToGameplayCueParameters)
	ADD_FUNCTION(HasHitResult)
	ADD_FUNCTION(GetHitResult)
	ADD_FUNCTION(HasOrigin)
	ADD_FUNCTION(GetOrigin)
	ADD_FUNCTION(HasEndPoint)
	ADD_FUNCTION(GetEndPoint)
	ADD_FUNCTION(GetEndPointTransform)
	ADD_FUNCTION(ToString)
	ADD_FUNCTION(GetScriptStruct)
	ADD_FUNCTION(ShouldCheckForTargetActorSwap)
	ADD_FUNCTION(ReplaceHitWith)
END_EXPORT_CLASS()
IMPLEMENT_EXPORTED_CLASS(FGameplayAbilityTargetData)
