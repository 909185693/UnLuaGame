// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UnLuaModuleInterface.h"


class LUASOCKET_API FLuaSocketModule : public IUnLuaModuleInterface
{
public:
	virtual void RegisterLuaLib(lua_State* L) override;
	virtual void UnRegisterLuaLib(lua_State* L) override;

protected:
	static int OpenLuaSocketFtp(lua_State* L);
	static int OpenLuaSocketHeaders(lua_State* L);
	static int OpenLuaSocketHttp(lua_State* L);
	static int OpenLuaSocketLtn12(lua_State* L);
	static int OpenLuaSocketMbox(lua_State* L);
	static int OpenLuaSocketMime(lua_State* L);
	static int OpenLuaSocketSmtp(lua_State* L);
	static int OpenLuaSocketSocket(lua_State* L);
	static int OpenLuaSocketTp(lua_State* L);
	static int OpenLuaSocketUrl(lua_State* L);
};
