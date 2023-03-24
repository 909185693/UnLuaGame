// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "Modules/ModuleManager.h"
#include "UnLuaGamePrivate.h"
#include "UnLuaGameSettings.h"
#include "LuaEnv.h"

#if WITH_EDITOR
#include "ISettingsModule.h"
#include "ISettingsSection.h"
#endif

#define LOCTEXT_NAMESPACE "FUnLuaGameModule"

DEFINE_LOG_CATEGORY(LogUnLuaGame)

/**
 * Cast a UObject
 */
int32 Global_Cast(lua_State* L)
{
	int32 NumParams = lua_gettop(L);
	if (NumParams < 2)
	{
		return luaL_error(L, "invalid parameters");
	}

	UObject* Object = UnLua::GetUObject(L, 1);
	if (!Object)
	{
		return 0;
	}

	UClass* Class = Cast<UClass>(UnLua::GetUObject(L, 2));
	if (Class && (Object->IsA(Class) || (Class->HasAnyClassFlags(CLASS_Interface) && Class != UInterface::StaticClass() && Object->GetClass()->ImplementsInterface(Class))))
	{
		lua_pushvalue(L, 1);
	}
	else
	{
		lua_pushnil(L);
	}
	return 1;
}

class FUnLuaGameModule : public IModuleInterface
{
public:
	/** IModuleInterface implementation */
	virtual void StartupModule() override
	{
		RegisterSettings();

		LuaEnvCreatedHandle = UnLua::FLuaEnv::OnCreated.AddRaw(this, &FUnLuaGameModule::OnLuaEnvCreated);

#if EXPORT_UNLUA_LUACJSON
		FModuleManager::Get().LoadModuleChecked(TEXT("LuaCJson"));
#endif

#if EXPORT_UNLUA_LUAPROTOBUF
		FModuleManager::Get().LoadModuleChecked(TEXT("LuaProtobuf"));
#endif

#if EXPORT_UNLUA_LUASOCKET
		FModuleManager::Get().LoadModuleChecked(TEXT("LuaSocket"));
#endif

#if EXPORT_UNLUA_LUAPANDA
		FModuleManager::Get().LoadModuleChecked(TEXT("LuaPanda"));
#endif

#if EXPORT_UNLUA_GAMEPLAYABILITIES
		FModuleManager::Get().LoadModuleChecked(TEXT("UnLuaGameplayAbilities"));
#endif

#if EXPORT_UNLUA_HEXNAVSYSTEM
		FModuleManager::Get().LoadModuleChecked(TEXT("UnLuaHexNavSystem"));
#endif

#if EXPORT_UNLUA_ENHANCEDINPUT
		FModuleManager::Get().LoadModuleChecked(TEXT("UnLuaEnhancedInput"));
#endif
	}

	virtual void ShutdownModule() override
	{
		UnregisterSettings();

		UnLua::FLuaEnv::OnCreated.Remove(LuaEnvCreatedHandle);
	}

	void RegisterSettings()
	{
#if WITH_EDITOR
		ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings");
		if (!SettingsModule)
			return;

		const auto Section = SettingsModule->RegisterSettings("Project", "Plugins", "UnLuaGame",
			LOCTEXT("UnLuaGameEditorSettingsName", "UnLuaGame"),
			LOCTEXT("UnLuaGameEditorSettingsDescription", "UnLuaGame Settings"),
			GetMutableDefault<UUnLuaGameSettings>());
		Section->OnModified().BindRaw(this, &FUnLuaGameModule::OnSettingsModified);
#endif
	}

	void UnregisterSettings()
	{
#if WITH_EDITOR
		ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings");
		if (SettingsModule)
			SettingsModule->UnregisterSettings("Project", "Plugins", "UnLuaGame");
#endif
	}

	bool OnSettingsModified()
	{
		return true;
	}

	void OnLuaEnvCreated(UnLua::FLuaEnv& LuaEnv)
	{
		lua_State* L = LuaEnv.GetMainState();

		lua_getglobal(L, "UE");
		lua_pushstring(L, "Cast");
		lua_pushcfunction(L, &Global_Cast);
		lua_rawset(L, -3);
		lua_pop(L, 2);

		#if UE_EDITOR
		lua_pushboolean(L, true);
		#else
		lua_pushboolean(L, false);
		#endif
		lua_setglobal(L, "UE_EDITOR");

		#if UE_GAME
		lua_pushboolean(L, true);
		#else
		lua_pushboolean(L, false);
		#endif
		lua_setglobal(L, "UE_GAME");

		#if UE_SERVER
		lua_pushboolean(L, true);
		#else
		lua_pushboolean(L, false);
		#endif
		lua_setglobal(L, "UE_SERVER");

		#if UE_BUILD_DEBUG
		lua_pushboolean(L, true);
		#else
		lua_pushboolean(L, false);
		#endif
		lua_setglobal(L, "UE_BUILD_DEBUG");

		#if UE_BUILD_DEVELOPMENT
		lua_pushboolean(L, true);
		#else
		lua_pushboolean(L, false);
		#endif
		lua_setglobal(L, "UE_BUILD_DEVELOPMENT");

		#if UE_BUILD_SHIPPING
		lua_pushboolean(L, true);
		#else
		lua_pushboolean(L, false);
		#endif
		lua_setglobal(L, "UE_BUILD_SHIPPING");

		#if PLATFORM_WINDOWS
		lua_pushboolean(L, true);
		#else
		lua_pushboolean(L, false);
		#endif
		lua_setglobal(L, "PLATFORM_WINDOWS");

		#if PLATFORM_LINUX
		lua_pushboolean(L, true);
		#else
		lua_pushboolean(L, false);
		#endif
		lua_setglobal(L, "PLATFORM_LINUX");

		#if PLATFORM_ANDROID
		lua_pushboolean(L, true);
		#else
		lua_pushboolean(L, false);
		#endif
		lua_setglobal(L, "PLATFORM_ANDROID");

		#if PLATFORM_IOS
		lua_pushboolean(L, true);
		#else
		lua_pushboolean(L, false);
		#endif
		lua_setglobal(L, "PLATFORM_IOS");

		#if PLATFORM_MAC
		lua_pushboolean(L, true);
		#else
		lua_pushboolean(L, false);
		#endif
		lua_setglobal(L, "PLATFORM_MAC");

		#if ENGINE_MAJOR_VERSION < 5 && PLATFORM_LUMIN
		lua_pushboolean(L, true);
		#else
		lua_pushboolean(L, false);
		#endif
		lua_setglobal(L, "PLATFORM_LUMIN");

		#if PLATFORM_SWITCH
		lua_pushboolean(L, true);
		#else
		lua_pushboolean(L, false);
		#endif
		lua_setglobal(L, "PLATFORM_SWITCH");

		#if PLATFORM_UNIX
		lua_pushboolean(L, true);
		#else
		lua_pushboolean(L, false);
		#endif
		lua_setglobal(L, "PLATFORM_UNIX");

		#ifdef PLATFORM_MICROSOFT
		#if PLATFORM_MICROSOFT
		lua_pushboolean(L, true);
		#else
		lua_pushboolean(L, false);
		#endif
		lua_setglobal(L, "PLATFORM_MICROSOFT");
		#endif // PLATFORM_MICROSOFT

		#if PLATFORM_HOLOLENS
		lua_pushboolean(L, true);
		#else
		lua_pushboolean(L, false);
		#endif
		lua_setglobal(L, "PLATFORM_HOLOLENS");

		#if ENGINE_MAJOR_VERSION < 5 && PLATFORM_XBOXONE
		lua_pushboolean(L, true);
		#else
		lua_pushboolean(L, false);
		#endif
		lua_setglobal(L, "PLATFORM_XBOXONE");
	}

private:
	FDelegateHandle LuaEnvCreatedHandle;
};



#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FUnLuaGameModule, UnLuaGame)