// Copyright 2022 CQUnreal. All Rights Reserved.

#include "UnLuaEx.h"
#include "LuaCore.h"
#include "LuaDynamicBinding.h"
#include "GameplayEffect.h"


static const luaL_Reg FGameplayEffectSpecLib[] =
{
	{ nullptr, nullptr }
};

BEGIN_EXPORT_REFLECTED_CLASS(FGameplayEffectSpec)
	ADD_FUNCTION(CopySetByCallerMagnitudes)
	ADD_FUNCTION(MergeSetByCallerMagnitudes)
	ADD_FUNCTION(HasValidCapturedAttributes)
	ADD_CONST_FUNCTION_EX("GetModifiedAttribute", const FGameplayEffectModifiedAttribute*, GetModifiedAttribute, const FGameplayAttribute&)
	ADD_FUNCTION(AddModifiedAttribute)
	ADD_FUNCTION(AttemptCalculateDurationFromDef)
	ADD_FUNCTION(SetDuration)
	ADD_FUNCTION(GetDuration)
	ADD_FUNCTION(GetPeriod)
#if ENGINE_MAJOR_VERSION >= 5 && ENGINE_MINOR_VERSION >= 3
	ADD_CONST_FUNCTION_EX("GetChanceToApplyToTarget", float, GetChanceToApplyToTarget)
#else
	ADD_FUNCTION(GetChanceToApplyToTarget)
#endif
	ADD_FUNCTION(SetContext)
	ADD_FUNCTION(GetContext)
	ADD_FUNCTION(GetAllGrantedTags)
	ADD_FUNCTION(GetAllAssetTags)
	ADD_FUNCTION_EX("SetSetByCallerMagnitudeByName", void, SetSetByCallerMagnitude, FName, float)
	ADD_FUNCTION_EX("SetSetByCallerMagnitude", void, SetSetByCallerMagnitude, FGameplayTag, float)
	ADD_CONST_FUNCTION_EX("GetSetByCallerMagnitudeByName", float, GetSetByCallerMagnitude, FName, bool, float)
	ADD_CONST_FUNCTION_EX("GetSetByCallerMagnitude", float, GetSetByCallerMagnitude, FGameplayTag, bool, float)
	ADD_FUNCTION(SetLevel)
	ADD_FUNCTION(GetLevel)
	ADD_FUNCTION(PrintAll)
	ADD_FUNCTION(ToSimpleString)
	ADD_FUNCTION(GetEffectContext)
	ADD_FUNCTION(DuplicateEffectContext)
	ADD_FUNCTION(CaptureAttributeDataFromTarget)
	ADD_FUNCTION(GetModifierMagnitude)
	ADD_FUNCTION(CalculateModifierMagnitudes)
	ADD_FUNCTION(RecaptureAttributeDataForClone)
	ADD_FUNCTION(RecaptureSourceActorTags)
	ADD_FUNCTION(SetupAttributeCaptureDefinitions)
	ADD_FUNCTION(CalculateModifiedDuration)
	ADD_LIB(FGameplayEffectSpecLib)
END_EXPORT_CLASS()
IMPLEMENT_EXPORTED_CLASS(FGameplayEffectSpec)
