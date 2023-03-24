// Copyright 2022 CQUnreal. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "UnLuaAIController.generated.h"

/**
 * AUnLuaAIController
 */
UCLASS()
class UNLUAGAME_API AUnLuaAIController : public AAIController
{
	GENERATED_UCLASS_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = Game)
	void StopBehaviorTree();

	/** Calculate minimal respawn delay */
	UFUNCTION(BlueprintNativeEvent, Category = AI)
	float GetMinRespawnDelay();

	/** State entered when inactive (no possessed pawn, not spectating, etc). */
	virtual void BeginInactiveState() override;

	/** Timer used by RoundEnded and Inactive states to accept player input again */
	UFUNCTION(BlueprintCallable, Category = AI)
	virtual void UnFreeze();

	UFUNCTION(BlueprintImplementableEvent, Category = Game, Meta = (DisplayName = "UnFreeze"))
	void ReceiveUnFreeze();

protected:
	/** Handle for efficient management of UnFreeze timer */
	FTimerHandle TimerHandle_UnFreeze;
};
