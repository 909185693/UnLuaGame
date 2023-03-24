// Copyright 2022 CQUnreal. All Rights Reserved.

#include "UnLuaEx.h"
#include "LuaCore.h"
#include "LuaDynamicBinding.h"
#include "DeviceProfiles/DeviceProfileManager.h"


static int32 UDeviceProfileManager_GetPlatformDeviceProfileName(lua_State* L)
{
	#if ENGINE_MAJOR_VERSION > 4 || (ENGINE_MAJOR_VERSION == 4 && ENGINE_MINOR_VERSION > 24)
	FString DeviceProfileName = UDeviceProfileManager::GetPlatformDeviceProfileName();
	#else
	FString DeviceProfileName = UDeviceProfileManager::GetActiveProfileName();
	#endif

	FTCHARToUTF8 UTF8CHAR_Ins(*DeviceProfileName);
	lua_pushlstring(L, (ANSICHAR*)(UTF8CHAR_Ins.Get()), UTF8CHAR_Ins.Length());
	return 1;
}


static const luaL_Reg UDeviceProfileManagerLib[] =
{
	{ "GetPlatformDeviceProfileName", UDeviceProfileManager_GetPlatformDeviceProfileName },
	{ nullptr, nullptr }
};

BEGIN_EXPORT_CLASS_EX(true, UDeviceProfileManager, UnLuaGame, UDeviceProfileManager, nullptr)
    ADD_LIB(UDeviceProfileManagerLib)
END_EXPORT_CLASS()
IMPLEMENT_EXPORTED_CLASS_EX(UDeviceProfileManager, UnLuaGame)
