// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Online.h"
#include "OnlineSessionSettings.h"

/**
 * General session settings for a UnLua game
 */
class FUnLuaOnlineGameSettings : public FOnlineSessionSettings
{
public:

	FUnLuaOnlineGameSettings(bool bIsLAN = false, bool bIsPresence = false, int32 MaxNumPlayers = 4);
	virtual ~FUnLuaOnlineGameSettings() {}
};

/**
 * General search setting for a Shooter game
 */
class FUnLuaOnlineSearchSettings : public FOnlineSessionSearch
{
public:
	FUnLuaOnlineSearchSettings(bool bSearchingLAN = false, bool bSearchingPresence = false);

	virtual ~FUnLuaOnlineSearchSettings() {}
};

/**
 * Search settings for an empty dedicated server to host a match
 */
class FUnLuaOnlineSearchSettingsEmptyDedicated : public FUnLuaOnlineSearchSettings
{
public:
	FUnLuaOnlineSearchSettingsEmptyDedicated(bool bSearchingLAN = false, bool bSearchingPresence = false);

	virtual ~FUnLuaOnlineSearchSettingsEmptyDedicated() {}
};
