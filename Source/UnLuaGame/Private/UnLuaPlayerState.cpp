// Copyright 2022 CQUnreal. All Rights Reserved.

#include "GameFramework/UnLuaPlayerState.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(UnLuaPlayerState)


AUnLuaPlayerState::AUnLuaPlayerState(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void AUnLuaPlayerState::OnDeactivated()
{
	ReceiveDeactivated();
}

void AUnLuaPlayerState::ReceiveDeactivated_Implementation()
{
	// By default we duplicate the inactive player state and destroy the old one
	Destroy();
}

void AUnLuaPlayerState::OnReactivated()
{
	ReceiveReactivated();
}

void AUnLuaPlayerState::ReceiveReactivated_Implementation()
{
	// Stub
}