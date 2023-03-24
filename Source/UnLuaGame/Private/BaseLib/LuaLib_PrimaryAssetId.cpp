// Copyright 2022 CQUnreal. All Rights Reserved.

#include "UnLuaEx.h"
#include "LuaCore.h"
#include "LuaDynamicBinding.h"
#include "UObject/PrimaryAssetId.h"

static int32 FPrimaryAssetId_New(lua_State* L)
{
	const int32 NumParams = lua_gettop(L);
	void* Userdata = NewTypedUserdata(L, FPrimaryAssetId);

	switch (NumParams)
	{
	case 1:
		new(Userdata) FPrimaryAssetId();
		break;
	case 2:
		new(Userdata) FPrimaryAssetId(UTF8_TO_TCHAR(lua_tostring(L, 2)));
		break;
	default:
		return luaL_error(L, "invalid parameters");
	}

	return 1;
}

static int32 FPrimaryAssetId_ToString(lua_State *L)
{
	int32 NumParams = lua_gettop(L);
	if (NumParams != 1)
	{
		return luaL_error(L, "invalid parameters for __tostring");
	}

	FPrimaryAssetId *AssetId = (FPrimaryAssetId*)GetCppInstanceFast(L, 1);
	if (!AssetId)
	{
		return luaL_error(L, "invalid FPrimaryAssetId");
	}

	lua_pushstring(L, TCHAR_TO_UTF8(*AssetId->ToString()));
	return 1;
}

static const luaL_Reg FPrimaryAssetIdLib[] =
{
	{ "__call", FPrimaryAssetId_New },
	{ "__tostring", FPrimaryAssetId_ToString },
	{ nullptr, nullptr }
};

// Export Actor Component
BEGIN_EXPORT_CLASS(FPrimaryAssetId, const FString&)
	ADD_FUNCTION_EX("IsValid", bool, IsValid)
	ADD_FUNCTION_EX("ToString", FString, ToString)
	ADD_STATIC_FUNCTION_EX("FromString", FPrimaryAssetId, FromString, const FString&)
	ADD_LIB(FPrimaryAssetIdLib)
END_EXPORT_CLASS()
IMPLEMENT_EXPORTED_CLASS(FPrimaryAssetId)

