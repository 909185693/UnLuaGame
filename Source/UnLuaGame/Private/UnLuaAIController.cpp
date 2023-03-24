// Copyright 2022 CQUnreal. All Rights Reserved.

#include "UnLuaAIController.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include "GameFramework/GameStateBase.h"
#include "BehaviorTree/BehaviorTreeComponent.h"


AUnLuaAIController::AUnLuaAIController(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void AUnLuaAIController::StopBehaviorTree()
{
	UBehaviorTreeComponent* BTComp = Cast<UBehaviorTreeComponent>(BrainComponent);
	if (BTComp != nullptr)
	{
		BTComp->StopTree(EBTStopMode::Safe);
	}
}

float AUnLuaAIController::GetMinRespawnDelay_Implementation()
{
	AGameStateBase const* const GameState = GetWorld()->GetGameState();
	if (GameState)
	{
		return GameState->GetPlayerRespawnDelay(this);
	}
	return 1.0f;
}

void AUnLuaAIController::BeginInactiveState()
{
	Super::BeginInactiveState();

	if ((GetPawn() != NULL) && (GetPawn()->Controller == this))
	{
		GetPawn()->Controller = NULL;
	}
	SetPawn(NULL);

	GetWorldTimerManager().SetTimer(TimerHandle_UnFreeze, this, &AUnLuaAIController::UnFreeze, GetMinRespawnDelay());
}

void AUnLuaAIController::UnFreeze()
{
	ReceiveUnFreeze();
}