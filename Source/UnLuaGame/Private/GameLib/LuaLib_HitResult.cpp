// Copyright 2022 CQUnreal. All Rights Reserved.

#include "UnLuaEx.h"
#include "LuaCore.h"
#include "LuaDynamicBinding.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "Engine/EngineTypes.h"

static int32 FHitResult_GetPhysMaterial(lua_State *L)
{
	int32 NumParams = lua_gettop(L);
	if (NumParams != 1)
	{
		return luaL_error(L, "invalid parameters");
	}

	FHitResult* HitResult = (FHitResult*)GetCppInstanceFast(L, 1);
	if (!HitResult)
	{
		return luaL_error(L, "invalid FHitResult");
	}

	if (HitResult->PhysMaterial.IsValid())
	{
		UnLua::PushUObject(L, HitResult->PhysMaterial.Get());
		return 1;
	}

	return 0;
}

static int32 FHitResult_GetSurfaceType(lua_State *L)
{
	int32 NumParams = lua_gettop(L);
	if (NumParams != 1)
	{
		return luaL_error(L, "invalid parameters");
	}

	FHitResult* HitResult = (FHitResult*)GetCppInstanceFast(L, 1);
	if (!HitResult)
	{
		return luaL_error(L, "invalid FHitResult");
	}

	if (HitResult->PhysMaterial.IsValid())
	{
		UnLua::Push(L, HitResult->PhysMaterial->SurfaceType);
		return 1;
	}

	return 0;
}

static const luaL_Reg FHitResultLib[] =
{
	{ "GetPhysMaterial", FHitResult_GetPhysMaterial },
	{ "GetSurfaceType", FHitResult_GetSurfaceType },
    { nullptr, nullptr }
};

BEGIN_EXPORT_REFLECTED_CLASS(FHitResult)
	ADD_FUNCTION(GetActor)
	ADD_FUNCTION(GetComponent)
	ADD_LIB(FHitResultLib)
END_EXPORT_CLASS()
IMPLEMENT_EXPORTED_CLASS(FHitResult)
