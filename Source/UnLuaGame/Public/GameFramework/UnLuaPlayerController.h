// Copyright 2022 CQUnreal. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "UnLuaPlayerController.generated.h"


UCLASS()
class UNLUAGAME_API AUnLuaPlayerController : public APlayerController
{
	GENERATED_UCLASS_BODY()

protected:
	virtual bool InputTouch(uint32 Handle, ETouchType::Type Type, const FVector2D& TouchLocation, float Force, FDateTime DeviceTimestamp, uint32 TouchpadIndex) override;

	UFUNCTION(BlueprintImplementableEvent, Category = Game, Meta = (DisplayName = "InputTouch"))
	void ReceiveInputTouch(int32 Handle, ETouchType::Type Type, const FVector2D& TouchLocation, float Force, int32 TouchpadIndex);

	virtual void ClientRestart_Implementation(APawn* NewPawn) override;

	UFUNCTION(BlueprintImplementableEvent, Category = Game, Meta = (DisplayName = "ClientRestart"))
	void ReceiveClientRestart(APawn* NewPawn);

	virtual void CleanupPlayerState() override;

	UFUNCTION(BlueprintNativeEvent, Category = Game, Meta = (DisplayName = "CleanupPlayerState"))
	void ReceiveCleanupPlayerState();

	virtual void PawnLeavingGame() override;

	UFUNCTION(BlueprintNativeEvent, Category = Game, Meta = (DisplayName = "PawnLeavingGame"))
	void ReceivePawnLeavingGame();

	/** Timer used by RoundEnded and Inactive states to accept player input again */
	virtual void UnFreeze() override;

	UFUNCTION(BlueprintImplementableEvent, Category = Game, Meta = (DisplayName = "UnFreeze"))
	void ReceiveUnFreeze();
};
