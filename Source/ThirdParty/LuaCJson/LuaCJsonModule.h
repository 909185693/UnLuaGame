// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UnLuaModuleInterface.h"


class LUACJSON_API FLuaCJsonModule : public IUnLuaModuleInterface
{
public:
	virtual void RegisterLuaLib(lua_State* L);
	virtual void UnRegisterLuaLib(lua_State* L);
};
