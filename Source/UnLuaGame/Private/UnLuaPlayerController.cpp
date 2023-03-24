// Copyright 2022 CQUnreal. All Rights Reserved.

#include "GameFramework/UnLuaPlayerController.h"
#include "GameFramework/PlayerState.h"


AUnLuaPlayerController::AUnLuaPlayerController(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

bool AUnLuaPlayerController::InputTouch(uint32 Handle, ETouchType::Type Type, const FVector2D& TouchLocation, float Force, FDateTime DeviceTimestamp, uint32 TouchpadIndex)
{
	bool bResult = Super::InputTouch(Handle, Type, TouchLocation, Force, DeviceTimestamp, TouchpadIndex);

	ReceiveInputTouch(Handle, Type, TouchLocation, Force, TouchpadIndex);

	return bResult;
}

void AUnLuaPlayerController::ClientRestart_Implementation(APawn* NewPawn)
{
	Super::ClientRestart_Implementation(NewPawn);

	ReceiveClientRestart(NewPawn);
}

void AUnLuaPlayerController::CleanupPlayerState()
{
	ReceiveCleanupPlayerState();
}

void AUnLuaPlayerController::ReceiveCleanupPlayerState_Implementation()
{
	APlayerController::CleanupPlayerState();
}

void AUnLuaPlayerController::PawnLeavingGame()
{
	ReceivePawnLeavingGame();
}

void AUnLuaPlayerController::ReceivePawnLeavingGame_Implementation()
{
	APlayerController::PawnLeavingGame();
}

void AUnLuaPlayerController::UnFreeze()
{
	Super::UnFreeze();

	ReceiveUnFreeze();
}