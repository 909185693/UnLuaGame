// Copyright 2022 CQUnreal. All Rights Reserved.

#include "UnLuaEx.h"
#include "LuaCore.h"
#include "LuaDynamicBinding.h"
#include "Engine/DataAsset.h"


static int32 UPrimaryDataAsset_ToString(lua_State *L)
{
	int32 NumParams = lua_gettop(L);
	if (NumParams != 1)
	{
		return luaL_error(L, "invalid parameters for __tostring");
	}

	UPrimaryDataAsset* DataAsset = Cast<UPrimaryDataAsset>(UnLua::GetUObject(L, 1));
	if (!DataAsset)
	{
		return luaL_error(L, "invalid UPrimaryDataAsset");
	}

	UnLua::Push(L, DataAsset->GetPrimaryAssetId().ToString());
	return 1;
}

static const luaL_Reg UPrimaryDataAssetLib[] =
{
	{ "ToString", UPrimaryDataAsset_ToString },
	{ "__tostring", UPrimaryDataAsset_ToString },
	{ nullptr, nullptr }
};

// Export Actor Component
BEGIN_EXPORT_REFLECTED_CLASS(UPrimaryDataAsset)
	ADD_FUNCTION(GetPrimaryAssetId)
	ADD_LIB(UPrimaryDataAssetLib)
END_EXPORT_CLASS()
IMPLEMENT_EXPORTED_CLASS(UPrimaryDataAsset)

