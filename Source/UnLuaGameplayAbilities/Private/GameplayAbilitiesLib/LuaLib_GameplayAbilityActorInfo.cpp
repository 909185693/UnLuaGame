// Copyright 2022 CQUnreal. All Rights Reserved.

#include "UnLuaEx.h"
#include "LuaCore.h"
#include "LuaDynamicBinding.h"
#include "Abilities/GameplayAbilityTypes.h"


BEGIN_EXPORT_REFLECTED_CLASS(FGameplayAbilityActorInfo)
	ADD_FUNCTION(GetAnimInstance)
	ADD_FUNCTION(IsLocallyControlled)
	ADD_FUNCTION(IsLocallyControlledPlayer)
	ADD_FUNCTION(IsNetAuthority)
	ADD_FUNCTION(InitFromActor)
	ADD_FUNCTION(SetAvatarActor)
	ADD_FUNCTION(ClearActorInfo)
END_EXPORT_CLASS()
IMPLEMENT_EXPORTED_CLASS(FGameplayAbilityActorInfo)
