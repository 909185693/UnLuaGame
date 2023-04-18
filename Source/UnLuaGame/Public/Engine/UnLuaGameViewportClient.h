// Copyright 2022 CQUnreal. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameViewportClient.h"
#include "UnLuaGameViewportClient.generated.h"

/**
 * 
 */
UCLASS()
class UNLUAGAME_API UUnLuaGameViewportClient : public UGameViewportClient
{
	GENERATED_UCLASS_BODY()

public:
	virtual bool InputTouch(FViewport* Viewport, int32 ControllerId, uint32 Handle, ETouchType::Type Type, const FVector2D& TouchLocation, float Force, FDateTime DeviceTimestamp, uint32 TouchpadIndex) override;
};
