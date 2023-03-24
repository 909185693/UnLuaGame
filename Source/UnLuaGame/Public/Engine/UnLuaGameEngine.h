// Copyright 2022 CQUnreal. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameEngine.h"
#include "UnLuaGameEngine.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class UNLUAGAME_API UUnLuaGameEngine : public UGameEngine
{
	GENERATED_UCLASS_BODY()

public:
	/**
	 * 	All regular engine handling, plus update ShooterKing state appropriately.
	 */
	virtual void HandleNetworkFailure(UWorld *World, UNetDriver *NetDriver, ENetworkFailure::Type FailureType, const FString& ErrorString) override;
};
