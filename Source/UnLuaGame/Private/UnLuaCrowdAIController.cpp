// Copyright 2022 CQUnreal. All Rights Reserved.

#include "GameFramework/UnLuaCrowdAIController.h"
#include "Navigation/CrowdFollowingComponent.h"


AUnLuaCrowdAIController::AUnLuaCrowdAIController(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>(TEXT("PathFollowingComponent")))
{

}