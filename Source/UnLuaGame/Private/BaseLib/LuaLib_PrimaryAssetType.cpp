// Copyright 2022 CQUnreal. All Rights Reserved.

#include "UnLuaEx.h"
#include "LuaCore.h"
#include "LuaDynamicBinding.h"
#include "UObject/PrimaryAssetId.h"

static int32 FPrimaryAssetType_New(lua_State* L)
{
	void* Userdata = NewTypedUserdata(L, FPrimaryAssetType);

	int32 NumParams = lua_gettop(L);
	switch (NumParams)
	{
	case 1:
		new(Userdata) FPrimaryAssetType();
		break;
	case 2:
		new(Userdata) FPrimaryAssetType(UTF8_TO_TCHAR(lua_tostring(L, 2)));
		break;
	default:
		return luaL_error(L, "invalid parameters");
	}

	return 1;
}

static int32 FPrimaryAssetType_ToString(lua_State *L)
{
	int32 NumParams = lua_gettop(L);
	if (NumParams != 1)
	{
		return luaL_error(L, "invalid parameters for __tostring");
	}

	FPrimaryAssetType* AssetType = (FPrimaryAssetType*)GetCppInstanceFast(L, 1);
	if (!AssetType)
	{
		return luaL_error(L, "invalid FPrimaryAssetType");
	}

	lua_pushstring(L, TCHAR_TO_UTF8(*AssetType->ToString()));
	return 1;
}


static const luaL_Reg FPrimaryAssetTypeLib[] =
{
	{ "__call", FPrimaryAssetType_New },
	{ "__tostring", FPrimaryAssetType_ToString },
	{ nullptr, nullptr }
};

// Export Actor Component
BEGIN_EXPORT_CLASS(FPrimaryAssetType, const FString&)
	ADD_FUNCTION_EX("IsValid", bool, IsValid)
	ADD_FUNCTION_EX("ToString", FString, ToString)
	ADD_LIB(FPrimaryAssetTypeLib)
END_EXPORT_CLASS()
IMPLEMENT_EXPORTED_CLASS(FPrimaryAssetType)

