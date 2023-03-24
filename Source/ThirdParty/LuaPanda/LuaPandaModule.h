// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UnLuaModuleInterface.h"


class LUAPANDA_API FLuaPandaModule : public IUnLuaModuleInterface
{
public:	
	virtual void RegisterLuaLib(lua_State* L) override;
	virtual void UnRegisterLuaLib(lua_State* L) override;

protected:
	static int OpenLuaPanda(lua_State* L);
};
