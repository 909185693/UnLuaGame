// Copyright 2022 CQUnreal. All Rights Reserved.

#include "UnLuaEx.h"
#include "LuaCore.h"
#include "LuaDynamicBinding.h"
#include "GameplayEffectTypes.h"


BEGIN_EXPORT_REFLECTED_CLASS(FGameplayEffectContextHandle)
	ADD_CONST_FUNCTION_EX("Get", const FGameplayEffectContext*, Get)
	ADD_FUNCTION(Clear)
	ADD_FUNCTION(IsValid)
	ADD_FUNCTION(GetOwnedGameplayTags)
	ADD_FUNCTION(AddInstigator)
	ADD_FUNCTION(GetAbility)
	ADD_FUNCTION(SetAbility)
	ADD_FUNCTION(GetInstigator)
	ADD_FUNCTION(GetAbilityInstance_NotReplicated)
	ADD_FUNCTION(GetAbilityLevel)
	ADD_FUNCTION(GetInstigatorAbilitySystemComponent)
	ADD_FUNCTION(GetEffectCauser)
	ADD_FUNCTION(GetOriginalInstigator)
	ADD_FUNCTION(GetOriginalInstigatorAbilitySystemComponent)
	ADD_FUNCTION(AddSourceObject)
	ADD_FUNCTION(GetSourceObject)
	ADD_FUNCTION(IsLocallyControlled)
	ADD_FUNCTION(IsLocallyControlledPlayer)
//	ADD_FUNCTION(GetActors)
//	ADD_FUNCTION(AddActors)
	ADD_FUNCTION(GetHitResult)
	ADD_FUNCTION(AddHitResult)
	ADD_FUNCTION(GetOrigin)
	ADD_FUNCTION(AddOrigin)
	ADD_FUNCTION(HasOrigin)
	ADD_FUNCTION(ToString)
	ADD_FUNCTION(Duplicate)
	ADD_FUNCTION_EX("__eq", bool, operator==, FGameplayEffectContextHandle const&)
END_EXPORT_CLASS()
IMPLEMENT_EXPORTED_CLASS(FGameplayEffectContextHandle)
