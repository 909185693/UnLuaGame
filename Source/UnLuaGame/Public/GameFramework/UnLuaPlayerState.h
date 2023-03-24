// Copyright 2022 CQUnreal. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "UnLuaPlayerState.generated.h"


UCLASS()
class UNLUAGAME_API AUnLuaPlayerState : public APlayerState
{
	GENERATED_UCLASS_BODY()

	/** Called on the server when the owning player has disconnected, by default this method destroys this player state */
	virtual void OnDeactivated() override;

	UFUNCTION(BlueprintNativeEvent, Category = Game, Meta = (DisplayName = "Deactivated"))
	void ReceiveDeactivated();

	/** Called on the server when the owning player has reconnected and this player state is added to the active players array */
	virtual void OnReactivated() override;

	UFUNCTION(BlueprintNativeEvent, Category = Game, Meta = (DisplayName = "Reactivated"))
	void ReceiveReactivated();
};
