// Copyright 2022 CQUnreal. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UnLuaGameSettings.generated.h"

/**
 * UUnLuaGameSettings
 */
UCLASS(Config = UnLuaGame, DefaultConfig, Meta = (DisplayName = "UnLua"))
class UNLUAGAME_API UUnLuaGameSettings : public UObject
{
	GENERATED_BODY()
	
public:
	UUnLuaGameSettings(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(Config, EditAnywhere, Category = "Runtime")
	bool bExportLuaCJsonLib = true;

	UPROPERTY(Config, EditAnywhere, Category = "Runtime")
	bool bExportLuaProtobufLib = true;

	UPROPERTY(Config, EditAnywhere, Category = "Runtime")
	bool bExportLuaSocketLib = true;

	UPROPERTY(Config, EditAnywhere, Category = "Runtime")
	bool bExportLuaPandaLib = true;

	UPROPERTY(Config, EditAnywhere, Category = "Runtime")
	bool bExportGameplayAbilitiesLib = false;

	UPROPERTY(Config, EditAnywhere, Category = "Runtime")
	bool bExportHexNavSystemLib = false;
};
