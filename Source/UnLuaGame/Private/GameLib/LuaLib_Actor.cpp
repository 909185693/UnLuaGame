// Copyright 2022 CQUnreal. All Rights Reserved.

#include "UnLuaEx.h"
#include "LuaCore.h"
#include "LuaDynamicBinding.h"
#include "GameFramework/Actor.h"

static int32 AActor_FinishSpawning(lua_State* L)
{
	int32 NumParams = lua_gettop(L);
	if (NumParams < 2)
	{
		return luaL_error(L, "invalid parameters");
	}

	AActor* Actor = Cast<AActor>(UnLua::GetUObject(L, 1));
	if (!Actor)
	{
		return luaL_error(L, "invalid AActor");
	}

	FTransform* TransformPtr = (FTransform*)GetCppInstanceFast(L, 2);
	if (!TransformPtr)
	{
		return luaL_error(L, "invalid FTransform");
	}

	bool bIsDefaultTransform = false;
	if (NumParams > 2)
	{
		bIsDefaultTransform = !!lua_toboolean(L, 3);
	}

	Actor->FinishSpawning(*TransformPtr, bIsDefaultTransform);
	return 0;
}

static const luaL_Reg AActorLib[] =
{
	{ "FinishSpawning", AActor_FinishSpawning },
    { nullptr, nullptr }
};

BEGIN_EXPORT_REFLECTED_CLASS(AActor)
	ADD_FUNCTION(GetNetMode)
	ADD_FUNCTION(IsNetMode)
	ADD_FUNCTION(ClearComponentOverlaps)
	ADD_FUNCTION(UpdateOverlaps)
    ADD_LIB(AActorLib)
END_EXPORT_CLASS()
IMPLEMENT_EXPORTED_CLASS(AActor)
