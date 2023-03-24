// Copyright 2022 CQUnreal. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UnLuaActor.generated.h"

UCLASS()
class UNLUAGAME_API AUnLuaActor : public AActor
{
	GENERATED_UCLASS_BODY()

	UFUNCTION(BlueprintImplementableEvent, meta = (BlueprintInternalUseOnly = "true", DisplayName = "PostInitializeComponents"))
	void ReceivePreInitializeComponents();

	virtual void PreInitializeComponents() override;

	UFUNCTION(BlueprintImplementableEvent, meta = (BlueprintInternalUseOnly = "true", DisplayName = "PostInitializeComponents"))
	void ReceivePostInitializeComponents();

	virtual void PostInitializeComponents() override;
};
