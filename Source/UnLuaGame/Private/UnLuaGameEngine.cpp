// Copyright 2022 CQUnreal. All Rights Reserved.

#include "Engine/UnLuaGameEngine.h"


UUnLuaGameEngine::UUnLuaGameEngine(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void UUnLuaGameEngine::HandleNetworkFailure(UWorld *World, UNetDriver *NetDriver, ENetworkFailure::Type FailureType, const FString& ErrorString)
{
	// standard failure handling.
	Super::HandleNetworkFailure(World, NetDriver, FailureType, ErrorString);
}