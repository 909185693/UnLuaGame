// Copyright 2022 CQUnreal. All Rights Reserved.

#include "UnLuaEx.h"
#include "LuaCore.h"
#include "LuaDynamicBinding.h"
#include "AbilitySystemComponent.h"
#include "Abilities/GameplayAbilityTypes.h"


/// <summary>
/// AbilitySystemComponentLib
/// </summary>

static const luaL_Reg AbilitySystemComponentLib[] =
{
    { nullptr, nullptr }
};

BEGIN_EXPORT_REFLECTED_CLASS(UAbilitySystemComponent)
	ADD_FUNCTION(BindToInputComponent)
	//ADD_FUNCTION(BindAbilityActivationToInputComponent)
	//ADD_FUNCTION(SetBlockAbilityBindingsArray)
	ADD_FUNCTION(AbilityLocalInputPressed)
	ADD_FUNCTION(AbilityLocalInputReleased)
	ADD_FUNCTION(LocalInputConfirm)
	ADD_FUNCTION(LocalInputCancel)
	ADD_FUNCTION(IsGenericConfirmInputBound)
	ADD_FUNCTION(IsGenericCancelInputBound)
	ADD_FUNCTION(PlayMontage)
	ADD_FUNCTION(PlayMontageSimulated)
	ADD_FUNCTION(CurrentMontageStop)
	ADD_FUNCTION(StopMontageIfCurrent)
	ADD_FUNCTION(ClearAnimatingAbility)
	ADD_FUNCTION(CurrentMontageJumpToSection)
	ADD_FUNCTION(CurrentMontageSetNextSectionName)
	ADD_FUNCTION(CurrentMontageSetPlayRate)
	ADD_FUNCTION(IsAnimatingAbility)
	ADD_FUNCTION(GetAnimatingAbility)
	ADD_FUNCTION(GetCurrentMontage)
	ADD_FUNCTION(GetCurrentMontageSectionID)
	ADD_FUNCTION(GetCurrentMontageSectionName)
	ADD_FUNCTION(GetCurrentMontageSectionLength)
	ADD_FUNCTION(GetCurrentMontageSectionTimeLeft)
	//ADD_FUNCTION(SetMontageRepAnimPositionMethod)
	#if ENGINE_MINOR_VERSION > 24
	ADD_FUNCTION(GetOwnerActor)
	ADD_FUNCTION(SetOwnerActor)
	ADD_FUNCTION(GetAvatarActor_Direct)
	ADD_FUNCTION(SetAvatarActor_Direct)
	#endif
	ADD_FUNCTION(GetAvatarActor)
	ADD_FUNCTION(SetAvatarActor)
	ADD_FUNCTION(InitAbilityActorInfo)
	ADD_FUNCTION(GetGameplayTaskAvatar)
	ADD_FUNCTION(RefreshAbilityActorInfo)
	ADD_FUNCTION(TryActivateAbility)
	ADD_FUNCTION(CancelAbility)
	ADD_FUNCTION(CancelAbilityHandle)
    ADD_LIB(AbilitySystemComponentLib)
END_EXPORT_CLASS()
IMPLEMENT_EXPORTED_CLASS(UAbilitySystemComponent)
