// Copyright 2022 CQUnreal. All Rights Reserved.

#include "UnLuaEx.h"
#include "LuaCore.h"
#include "LuaDynamicBinding.h"
#include "Engine/GameInstance.h"
#include "Engine/DemoNetDriver.h"


static int32 UGameInstance_StartRecordingReplay(lua_State* L)
{
	int32 NumParams = lua_gettop(L);
	if (NumParams < 2)
		return luaL_error(L, "invalid parameters");

	UGameInstance* GameInstance = Cast<UGameInstance>(UnLua::GetUObject(L, 1));
	if (!GameInstance)
	{
		return luaL_error(L, "invalid UGameInstance");
	}
	
	FString Name;
	if (NumParams > 1)
	{
		Name = UTF8_TO_TCHAR(lua_tostring(L, 2));
	}

	FString FriendlyName;
	if (NumParams > 2)
	{
		FriendlyName = UTF8_TO_TCHAR(lua_tostring(L, 3));
	}

	TArray<FString> AdditionalOptions;
	if (NumParams > 3)
	{
		FScriptArray* ScriptArray = UnLua::GetArray(L, 4);
		if (!ScriptArray)
			return luaL_error(L, "invalid TArray<FString>");

		AdditionalOptions = *(TArray<FString>*)ScriptArray;
	}

	GameInstance->StartRecordingReplay(Name, FriendlyName, AdditionalOptions);

	return 0;
}

static int32 UGameInstance_GetDemoTotalTime(lua_State* L)
{
	int32 NumParams = lua_gettop(L);
	if (NumParams < 1)
		return luaL_error(L, "invalid parameters");

	UGameInstance* GameInstance = Cast<UGameInstance>(UnLua::GetUObject(L, 1));
	if (!GameInstance)
	{
		return luaL_error(L, "invalid UGameInstance");
	}

	UWorld* World = GameInstance->GetWorld();
	UDemoNetDriver* DemoNetDriver = World ? World->GetDemoNetDriver() : nullptr;
	if (DemoNetDriver != nullptr)
	{
		lua_pushnumber(L, DemoNetDriver->GetDemoTotalTime());
		return 1;
	}

	lua_pushnumber(L, 0.f);
	return 1;
}

static int32 UGameInstance_GetDemoCurrentTimeInMS(lua_State* L)
{
	int32 NumParams = lua_gettop(L);
	if (NumParams < 1)
		return luaL_error(L, "invalid parameters");

	UGameInstance* GameInstance = Cast<UGameInstance>(UnLua::GetUObject(L, 1));
	if (!GameInstance)
	{
		return luaL_error(L, "invalid UGameInstance");
	}

	UWorld* World = GameInstance->GetWorld();
	UDemoNetDriver* DemoNetDriver = World ? World->GetDemoNetDriver() : nullptr;
	if (DemoNetDriver != nullptr)
	{
		lua_pushnumber(L, DemoNetDriver->GetDemoCurrentTimeInMS());
		return 1;
	}

	lua_pushnumber(L, 0);
	return 1;
}

static int32 UGameInstance_GetDemoCurrentTime(lua_State* L)
{
	int32 NumParams = lua_gettop(L);
	if (NumParams < 1)
		return luaL_error(L, "invalid parameters");

	UGameInstance* GameInstance = Cast<UGameInstance>(UnLua::GetUObject(L, 1));
	if (!GameInstance)
	{
		return luaL_error(L, "invalid UGameInstance");
	}

	UWorld* World = GameInstance->GetWorld();
	UDemoNetDriver* DemoNetDriver = World ? World->GetDemoNetDriver() : nullptr;
	if (DemoNetDriver != nullptr)
	{
		lua_pushnumber(L, DemoNetDriver->GetDemoCurrentTime());
		return 1;
	}

	lua_pushnumber(L, 0.f);
	return 1;
}

static int32 UGameInstance_SetDemoCurrentTime(lua_State* L)
{
	int32 NumParams = lua_gettop(L);
	if (NumParams < 2)
		return luaL_error(L, "invalid parameters");

	UGameInstance* GameInstance = Cast<UGameInstance>(UnLua::GetUObject(L, 1));
	if (!GameInstance)
	{
		return luaL_error(L, "invalid UGameInstance");
	}

	float CurrentTime = lua_tonumber(L, 2);

	UWorld* World = GameInstance->GetWorld();
	UDemoNetDriver* DemoNetDriver = World ? World->GetDemoNetDriver() : nullptr;
	if (DemoNetDriver != nullptr)
	{
		DemoNetDriver->SetDemoCurrentTime(CurrentTime);
		return 0;
	}

	return 0;
}

static int32 UGameInstance_GotoTimeInSeconds(lua_State* L)
{
	int32 NumParams = lua_gettop(L);
	if (NumParams < 2)
		return luaL_error(L, "invalid parameters");

	UGameInstance* GameInstance = Cast<UGameInstance>(UnLua::GetUObject(L, 1));
	if (!GameInstance)
	{
		return luaL_error(L, "invalid UGameInstance");
	}

	float CurrentTime = lua_tonumber(L, 2);

	UWorld* World = GameInstance->GetWorld();
	UDemoNetDriver* DemoNetDriver = World ? World->GetDemoNetDriver() : nullptr;
	if (DemoNetDriver != nullptr)
	{
		DemoNetDriver->GotoTimeInSeconds(CurrentTime);
		return 0;
	}

	return 0;
}

static int32 UGameInstance_GetDemoPath(lua_State* L)
{
	int32 NumParams = lua_gettop(L);
	if (NumParams < 1)
		return luaL_error(L, "invalid parameters");

	UGameInstance* GameInstance = Cast<UGameInstance>(UnLua::GetUObject(L, 1));
	if (!GameInstance)
	{
		return luaL_error(L, "invalid UGameInstance");
	}

	UWorld* World = GameInstance->GetWorld();
	UDemoNetDriver* DemoNetDriver = World ? World->GetDemoNetDriver() : nullptr;
	if (DemoNetDriver != nullptr)
	{
		lua_pushstring(L, TCHAR_TO_UTF8(*DemoNetDriver->GetDemoPath()));
		return 1;
	}

	lua_pushstring(L, "");
	return 1;
}

static int32 UGameInstance_GetDemoFrameNum(lua_State* L)
{
	int32 NumParams = lua_gettop(L);
	if (NumParams < 1)
		return luaL_error(L, "invalid parameters");

	UGameInstance* GameInstance = Cast<UGameInstance>(UnLua::GetUObject(L, 1));
	if (!GameInstance)
	{
		return luaL_error(L, "invalid UGameInstance");
	}

	UWorld* World = GameInstance->GetWorld();
	UDemoNetDriver* DemoNetDriver = World ? World->GetDemoNetDriver() : nullptr;
	if (DemoNetDriver != nullptr)
	{
		lua_pushnumber(L, DemoNetDriver->GetDemoFrameNum());
		return 1;
	}

	lua_pushnumber(L, 0);
	return 1;
}

static int32 UGameInstance_GetDemoURL(lua_State* L)
{
	int32 NumParams = lua_gettop(L);
	if (NumParams < 1)
		return luaL_error(L, "invalid parameters");

	UGameInstance* GameInstance = Cast<UGameInstance>(UnLua::GetUObject(L, 1));
	if (!GameInstance)
	{
		return luaL_error(L, "invalid UGameInstance");
	}

	UWorld* World = GameInstance->GetWorld();
	UDemoNetDriver* DemoNetDriver = World ? World->GetDemoNetDriver() : nullptr;
	if (DemoNetDriver != nullptr)
	{
		lua_pushstring(L, TCHAR_TO_UTF8(*DemoNetDriver->GetDemoURL()));
		return 1;
	}

	lua_pushstring(L, "");
	return 1;
}

static int32 UGameInstance_IsDemoPlaying(lua_State* L)
{
	int32 NumParams = lua_gettop(L);
	if (NumParams < 1)
		return luaL_error(L, "invalid parameters");

	UGameInstance* GameInstance = Cast<UGameInstance>(UnLua::GetUObject(L, 1));
	if (!GameInstance)
	{
		return luaL_error(L, "invalid UGameInstance");
	}

	UWorld* World = GameInstance->GetWorld();
	UDemoNetDriver* DemoNetDriver = World ? World->GetDemoNetDriver() : nullptr;
	if (DemoNetDriver != nullptr)
	{
		lua_pushboolean(L, DemoNetDriver->IsPlaying());
		return 1;
	}

	lua_pushboolean(L, false);
	return 1;
}

static int32 UGameInstance_IsDemoRecording(lua_State* L)
{
	int32 NumParams = lua_gettop(L);
	if (NumParams < 1)
		return luaL_error(L, "invalid parameters");

	UGameInstance* GameInstance = Cast<UGameInstance>(UnLua::GetUObject(L, 1));
	if (!GameInstance)
	{
		return luaL_error(L, "invalid UGameInstance");
	}

	UWorld* World = GameInstance->GetWorld();
	UDemoNetDriver* DemoNetDriver = World ? World->GetDemoNetDriver() : nullptr;
	if (DemoNetDriver != nullptr)
	{
		lua_pushboolean(L, DemoNetDriver->IsRecording());
		return 1;
	}

	lua_pushboolean(L, false);
	return 1;
}

static int32 UGameInstance_IsDemoRecordingPaused(lua_State* L)
{
	int32 NumParams = lua_gettop(L);
	if (NumParams < 1)
		return luaL_error(L, "invalid parameters");

	UGameInstance* GameInstance = Cast<UGameInstance>(UnLua::GetUObject(L, 1));
	if (!GameInstance)
	{
		return luaL_error(L, "invalid UGameInstance");
	}

	UWorld* World = GameInstance->GetWorld();
	UDemoNetDriver* DemoNetDriver = World ? World->GetDemoNetDriver() : nullptr;
	if (DemoNetDriver != nullptr)
	{
		lua_pushboolean(L, DemoNetDriver->IsRecordingPaused());
		return 1;
	}

	lua_pushboolean(L, false);
	return 1;
}

static int32 UGameInstance_PauseDemo(lua_State* L)
{
	int32 NumParams = lua_gettop(L);
	if (NumParams < 2)
		return luaL_error(L, "invalid parameters");

	UGameInstance* GameInstance = Cast<UGameInstance>(UnLua::GetUObject(L, 1));
	if (!GameInstance)
	{
		return luaL_error(L, "invalid UGameInstance");
	}

	bool bPause = !!lua_toboolean(L, 2);

	UWorld* World = GameInstance->GetWorld();
	AWorldSettings* WorldSettings = World ? World->GetWorldSettings() : nullptr;
	if (WorldSettings != nullptr)
	{
		APlayerState* PauserPlayerState = WorldSettings->GetPauserPlayerState();
		if (bPause && PauserPlayerState == nullptr)
		{
			UDemoNetDriver* DemoNetDriver = World->GetDemoNetDriver();
			if (DemoNetDriver && DemoNetDriver->ServerConnection && DemoNetDriver->ServerConnection->OwningActor)
			{
				APlayerController* PlayerController = Cast<APlayerController>(DemoNetDriver->ServerConnection->OwningActor);
				if (IsValid(PlayerController))
				{
					WorldSettings->SetPauserPlayerState(PlayerController->PlayerState);
				}
			}
		}
		else if (!bPause && PauserPlayerState)
		{
			WorldSettings->SetPauserPlayerState(nullptr);
		}
	}

	return 0;
}

static int32 UGameInstance_SetDemoPlayTimeDilation(lua_State* L)
{
	int32 NumParams = lua_gettop(L);
	if (NumParams < 2)
		return luaL_error(L, "invalid parameters");

	UGameInstance* GameInstance = Cast<UGameInstance>(UnLua::GetUObject(L, 1));
	if (!GameInstance)
	{
		return luaL_error(L, "invalid UGameInstance");
	}

	float PlayTimeDilation = lua_tonumber(L, 2);

	UWorld* World = GameInstance->GetWorld();
	AWorldSettings* WorldSettings = World ? World->GetWorldSettings() : nullptr;
	if (WorldSettings != nullptr)
	{
		WorldSettings->DemoPlayTimeDilation = PlayTimeDilation;
		return 0;
	}

	return 0;
}

static const luaL_Reg UGameInstanceLib[] =
{
	{ "StartRecordingReplay", UGameInstance_StartRecordingReplay },
	{ "GetDemoTotalTime", UGameInstance_GetDemoTotalTime },
	{ "GetDemoCurrentTimeInMS", UGameInstance_GetDemoCurrentTimeInMS },
	{ "GetDemoCurrentTime", UGameInstance_GetDemoCurrentTime },
	{ "SetDemoCurrentTime", UGameInstance_SetDemoCurrentTime },
	{ "GotoTimeInSeconds", UGameInstance_GotoTimeInSeconds },
	{ "GetDemoPath", UGameInstance_GetDemoPath },
	{ "GetDemoFrameNum", UGameInstance_GetDemoFrameNum },
	{ "GetDemoURL", UGameInstance_GetDemoURL },
	{ "IsDemoPlaying", UGameInstance_IsDemoPlaying },
	{ "IsDemoRecording", UGameInstance_IsDemoRecording },
	{ "IsDemoRecordingPaused", UGameInstance_IsDemoRecordingPaused },
	{ "PauseDemo", UGameInstance_PauseDemo },
	{ "SetDemoPlayTimeDilation", UGameInstance_SetDemoPlayTimeDilation },
    { nullptr, nullptr }
};

BEGIN_EXPORT_REFLECTED_CLASS(UGameInstance)
	ADD_FUNCTION(StopRecordingReplay)
	ADD_FUNCTION(PlayReplay)
    ADD_LIB(UGameInstanceLib)
END_EXPORT_CLASS()
IMPLEMENT_EXPORTED_CLASS(UGameInstance)
