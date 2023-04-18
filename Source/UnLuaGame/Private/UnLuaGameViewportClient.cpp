// Copyright 2022 CQUnreal. All Rights Reserved.

#include "Engine/UnLuaGameViewportClient.h"
#include "Engine/Console.h"
#include "Engine/LocalPlayer.h"

UUnLuaGameViewportClient::UUnLuaGameViewportClient(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

bool UUnLuaGameViewportClient::InputTouch(FViewport* InViewport, int32 ControllerId, uint32 Handle, ETouchType::Type Type, const FVector2D& TouchLocation, float Force, FDateTime DeviceTimestamp, uint32 TouchpadIndex)
{
	if (IgnoreInput())
	{
		return false;
	}

	ULocalPlayer* LocalPlayer = GetGameInstance()->GetLocalPlayerByIndex(0);

	// route to subsystems that care
	bool bResult = (ViewportConsole ? ViewportConsole->InputTouch(LocalPlayer ? LocalPlayer->GetControllerId() : ControllerId, Handle, Type, TouchLocation, Force, DeviceTimestamp, TouchpadIndex) : false);
	if (!bResult)
	{
		ULocalPlayer* const TargetPlayer = LocalPlayer ? LocalPlayer : GEngine->GetLocalPlayerFromControllerId(this, ControllerId);
		if (TargetPlayer && TargetPlayer->PlayerController)
		{
			bResult = TargetPlayer->PlayerController->InputTouch(Handle, Type, TouchLocation, Force, DeviceTimestamp, TouchpadIndex);
		}
	}

	return bResult;
}