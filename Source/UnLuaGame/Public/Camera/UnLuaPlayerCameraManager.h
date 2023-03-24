// Copyright 2022 CQUnreal. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include "UnLuaPlayerCameraManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnUpdateCamera, float, DeltaTime, const FRotator&, CameraRotation, const FVector&, CameraLocation);

UCLASS()
class UNLUAGAME_API AUnLuaPlayerCameraManager : public APlayerCameraManager
{
	GENERATED_UCLASS_BODY()

	/**
	 * Performs per-tick camera update. Called once per tick after all other actors have been ticked.
	 * Non-local players replicate the POV if bUseClientSideCameraUpdates is true.
	 */
	virtual void UpdateCamera(float DeltaTime) override;

public:
	UFUNCTION(BlueprintImplementableEvent, Category = Game, Meta = (DisplayName = "Camera"))
	void ReceiveUpdateCamera(float DeltaTime);

public:
	UPROPERTY(BlueprintAssignable)
	FOnUpdateCamera OnUpdateCamera;
};
