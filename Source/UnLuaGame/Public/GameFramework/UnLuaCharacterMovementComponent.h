// Copyright 2022 CQUnreal. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UnLuaCharacterMovementComponent.generated.h"


UCLASS()
class UNLUAGAME_API UUnLuaCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_UCLASS_BODY()

	virtual float GetMaxSpeed() const override;

	UFUNCTION(BlueprintNativeEvent)
	float K2_GetMaxSpeed() const;
};
