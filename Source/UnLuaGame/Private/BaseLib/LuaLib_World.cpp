// Copyright 2022 CQUnreal. All Rights Reserved.

#include "UnLuaEx.h"
#include "LuaCore.h"
#include "LuaDynamicBinding.h"
#include "Engine/World.h"


static int32 UWorld_SpawnActorDeferred(lua_State* L)
{
	int32 NumParams = lua_gettop(L);
	if (NumParams < 2)
	{
		return luaL_error(L, "invalid parameters");
	}

	UWorld* World = Cast<UWorld>(UnLua::GetUObject(L, 1));
	if (!World)
	{
		return luaL_error(L, "invalid world");
	}

	UClass* Class = Cast<UClass>(UnLua::GetUObject(L, 2));
	if (!Class)
	{
		return luaL_error(L, "invalid actor class");
	}

	FTransform Transform;
	if (NumParams > 2)
	{
		FTransform* TransformPtr = (FTransform*)GetCppInstanceFast(L, 3);
		if (TransformPtr)
		{
			Transform = *TransformPtr;
		}
	}

	FActorSpawnParameters SpawnParameters;
	if (NumParams > 3)
	{
		uint8 CollisionHandlingOverride = (uint8)lua_tointeger(L, 4);
		SpawnParameters.SpawnCollisionHandlingOverride = (ESpawnActorCollisionHandlingMethod)CollisionHandlingOverride;
	}
	if (NumParams > 4)
	{
		AActor* Owner = Cast<AActor>(UnLua::GetUObject(L, 5));
		check(!Owner || (Owner && World == Owner->GetWorld()));
		SpawnParameters.Owner = Owner;
	}
	if (NumParams > 5)
	{
		AActor* Actor = Cast<AActor>(UnLua::GetUObject(L, 6));
		if (Actor)
		{
			APawn* Instigator = Cast<APawn>(Actor);
			if (!Instigator)
			{
				Instigator = Actor->GetInstigator();
			}
			SpawnParameters.Instigator = Instigator;
		}
	}

	{
		const char* ModuleName = NumParams > 6 ? lua_tostring(L, 7) : nullptr;
		int32 TableRef = INDEX_NONE;
		if (NumParams > 7 && lua_type(L, 8) == LUA_TTABLE)
		{
			lua_pushvalue(L, 8);
			TableRef = luaL_ref(L, LUA_REGISTRYINDEX);
		}
		FScopedLuaDynamicBinding Binding(L, Class, UTF8_TO_TCHAR(ModuleName), TableRef);
		AActor* NewActor = World->SpawnActorDeferred<AActor>(Class, Transform, SpawnParameters.Owner, SpawnParameters.Instigator, SpawnParameters.SpawnCollisionHandlingOverride);
		UnLua::PushUObject(L, NewActor);
	}

	return 1;
}

static int32 UWorld_EncroachingBlockingGeometry(lua_State* L)
{
	int32 NumParams = lua_gettop(L);
	if (NumParams != 4)
	{
		return luaL_error(L, "invalid parameters");
	}

	UWorld* World = Cast<UWorld>(UnLua::GetUObject(L, 1));
	if (!World)
	{
		return luaL_error(L, "invalid world");
	}

	AActor* TestActor = Cast<AActor>(UnLua::GetUObject(L, 2));
	if (!TestActor)
	{
		return luaL_error(L, "invalid TestActor");
	}

	FVector* TestLocation = (FVector*)GetCppInstanceFast(L, 3);
	if (!TestLocation)
	{
		return luaL_error(L, "invalid TestLocation");
	}

	FRotator* TestRotation = (FRotator*)GetCppInstanceFast(L, 4);
	if (!TestRotation)
	{
		return luaL_error(L, "invalid TestRotation");
	}

	bool bResult = World->EncroachingBlockingGeometry(TestActor, *TestLocation, *TestRotation);
	lua_pushboolean(L, bResult);
	return 1;
}

static int32 UWorld_GetMapName(lua_State* L)
{
	int32 NumParams = lua_gettop(L);
	if (NumParams != 1)
	{
		return luaL_error(L, "invalid parameters");
	}

	UWorld* World = Cast<UWorld>(UnLua::GetUObject(L, 1));
	if (!World)
	{
		return luaL_error(L, "invalid world");
	}

	lua_pushstring(L, TCHAR_TO_ANSI(*GetNameSafe(World)));
	return 1;
}

static int32 UWorld_GetGameModeAlias(lua_State* L)
{
	int32 NumParams = lua_gettop(L);
	if (NumParams != 1)
	{
		return luaL_error(L, "invalid parameters");
	}

	UWorld* World = Cast<UWorld>(UnLua::GetUObject(L, 1));
	if (!World)
	{
		return luaL_error(L, "invalid world");
	}

	FString Options;
	FString GameParam;
	for (int32 i = 0; i < World->URL.Op.Num(); i++)
	{
		Options += TEXT("?");
		Options += World->URL.Op[i];
		FParse::Value(*World->URL.Op[i], TEXT("GAME="), GameParam);
	}

	lua_pushstring(L, TCHAR_TO_ANSI(*GameParam));
	return 1;
}

static int32 UWorld_GetURL(lua_State* L)
{
	int32 NumParams = lua_gettop(L);
	if (NumParams != 1)
	{
		return luaL_error(L, "invalid parameters");
	}

	UWorld* World = Cast<UWorld>(UnLua::GetUObject(L, 1));
	if (!World)
	{
		return luaL_error(L, "invalid world");
	}

	void* Userdata = NewTypedUserdata(L, FURL);
	new(Userdata) FURL(World->URL);

	return 1;
}

static const luaL_Reg UWorldLib[] =
{
	{ "SpawnActorDeferred", UWorld_SpawnActorDeferred },
	{ "EncroachingBlockingGeometry", UWorld_EncroachingBlockingGeometry},
	{ "GetMapName", UWorld_GetMapName },
	{ "GetGameModeAlias", UWorld_GetGameModeAlias },
	{ "GetURL", UWorld_GetURL },
    { nullptr, nullptr }
};

BEGIN_EXPORT_CLASS_EX(true, UWorld, UnLuaGame, UWorld, nullptr)
	ADD_CONST_FUNCTION_EX("IsPlayInEditor",bool,IsPlayInEditor)
	ADD_CONST_FUNCTION_EX("IsPlayInPreview", bool, IsPlayInPreview)
	ADD_CONST_FUNCTION_EX("IsPlayInMobilePreview", bool, IsPlayInMobilePreview)
	ADD_CONST_FUNCTION_EX("IsPlayInVulkanPreview", bool, IsPlayInVulkanPreview)
	ADD_CONST_FUNCTION_EX("IsGameWorld", bool, IsGameWorld)
	ADD_CONST_FUNCTION_EX("IsEditorWorld", bool, IsEditorWorld)
	ADD_CONST_FUNCTION_EX("IsPreviewWorld", bool, IsPreviewWorld)
	ADD_CONST_FUNCTION_EX("IsPlayingReplay", bool, IsPlayingReplay)
	ADD_CONST_FUNCTION_EX("IsPlayingClientReplay", bool, IsPlayingClientReplay)
	ADD_CONST_FUNCTION_EX("IsRecordingReplay", bool, IsRecordingReplay)
	ADD_CONST_FUNCTION_EX("IsRecordingClientReplay", bool, IsRecordingClientReplay)
	ADD_CONST_FUNCTION_EX("UsesGameHiddenFlags", bool, UsesGameHiddenFlags)
    ADD_LIB(UWorldLib)
END_EXPORT_CLASS()
IMPLEMENT_EXPORTED_CLASS_EX(UWorld, UnLuaGame)
