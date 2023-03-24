// Copyright 2022 CQUnreal. All Rights Reserved.

#include "UnLuaEx.h"
#include "LuaCore.h"
#include "LuaDynamicBinding.h"
#include "GameplayTask.h"

BEGIN_EXPORT_REFLECTED_CLASS(UGameplayTask)
	ADD_FUNCTION(ExternalConfirm)
	ADD_FUNCTION(ExternalCancel)
	ADD_FUNCTION(GetOwnerActor)
	ADD_FUNCTION(GetAvatarActor)
	ADD_FUNCTION(IsSupportedForNetworking)
	ADD_FUNCTION(GetInstanceName)
	ADD_FUNCTION(IsTickingTask)
	ADD_FUNCTION(IsSimulatedTask)
	ADD_FUNCTION(IsSimulating)
	ADD_FUNCTION(IsPausable)
	ADD_FUNCTION(HasOwnerFinished)
	ADD_FUNCTION(RequiresPriorityOrResourceManagement)
	//ADD_FUNCTION(GetState)
	ADD_FUNCTION(IsActive)
	ADD_FUNCTION(IsPaused)
	ADD_FUNCTION(IsFinished)
	ADD_FUNCTION(GetChildTask)
	ADD_FUNCTION_EX("GetGameplayTasksComponent", UGameplayTasksComponent*, GetGameplayTasksComponent)
	ADD_FUNCTION(IsOwnedByTasksComponent)
	ADD_FUNCTION_EX("AddRequiredResource", void, AddRequiredResource, TSubclassOf<UGameplayTaskResource>)
	ADD_FUNCTION_EX("AddRequiredResourceArray", void, AddRequiredResourceSet, const TArray<TSubclassOf<UGameplayTaskResource> >&)
	ADD_FUNCTION_EX("AddRequiredResourceSet", void, AddRequiredResourceSet, FGameplayResourceSet)
	ADD_FUNCTION_EX("AddClaimedResource", void, AddClaimedResource, TSubclassOf<UGameplayTaskResource>)
	ADD_FUNCTION_EX("AddClaimedResourceArray", void, AddClaimedResourceSet, const TArray<TSubclassOf<UGameplayTaskResource> >&)
	ADD_FUNCTION_EX("AddClaimedResourceSet", void, AddClaimedResourceSet, FGameplayResourceSet)
	//ADD_FUNCTION(GetResourceOverlapPolicy)
	ADD_FUNCTION(IsWaitingOnRemotePlayerdata)
	ADD_FUNCTION(IsWaitingOnAvatar)
END_EXPORT_CLASS()
IMPLEMENT_EXPORTED_CLASS(UGameplayTask)
