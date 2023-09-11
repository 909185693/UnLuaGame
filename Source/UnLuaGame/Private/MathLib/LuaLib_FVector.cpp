// Copyright 2022 CQUnreal. All Rights Reserved.

#include "UnLuaEx.h"
#include "MathLib/LuaLib_Math.h"

static int32 FVector_ToVector(lua_State* L)
{
	FVector* V = (FVector*)GetCppInstanceFast(L, 1);
	if (!V)
	{
		return luaL_error(L, "invalid FVector");
	}

	void* Userdata = NewTypedUserdata(L, FVector);
	new(Userdata) FVector(*V);
	return 1;
}

static int32 FVector_ToVector2D(lua_State* L)
{
	FVector* V = (FVector*)GetCppInstanceFast(L, 1);
	if (!V)
	{
		return luaL_error(L, "invalid FVector");
	}

	void* Userdata = NewTypedUserdata(L, FVector2D);
	new(Userdata) FVector2D(*V);
	return 1;
}

static int32 FVector_ToVector4(lua_State* L)
{
	FVector* V = (FVector*)GetCppInstanceFast(L, 1);
	if (!V)
	{
		return luaL_error(L, "invalid FVector");
	}

	void* Userdata = NewTypedUserdata(L, FVector4);
	new(Userdata) FVector4(*V);
	return 1;
}

static int32 FVector_ToNetQuantize(lua_State* L)
{
	FVector* V = (FVector*)GetCppInstanceFast(L, 1);
	if (!V)
	{
		return luaL_error(L, "invalid FVector");
	}

	void* Userdata = NewTypedUserdata(L, FVector_NetQuantize);
	new(Userdata) FVector_NetQuantize(*V);
	return 1;
}

static int32 FVector_ToNetQuantize10(lua_State* L)
{
	FVector* V = (FVector*)GetCppInstanceFast(L, 1);
	if (!V)
	{
		return luaL_error(L, "invalid FVector");
	}

	void* Userdata = NewTypedUserdata(L, FVector_NetQuantize10);
	new(Userdata) FVector_NetQuantize10(*V);
	return 1;
}

static int32 FVector_ToNetQuantize100(lua_State* L)
{
	FVector* V = (FVector*)GetCppInstanceFast(L, 1);
	if (!V)
	{
		return luaL_error(L, "invalid FVector");
	}

	void* Userdata = NewTypedUserdata(L, FVector_NetQuantize100);
	new(Userdata) FVector_NetQuantize100(*V);
	return 1;
}

static int32 FVector_ToNetQuantizeNormal(lua_State* L)
{
	FVector* V = (FVector*)GetCppInstanceFast(L, 1);
	if (!V)
	{
		return luaL_error(L, "invalid FVector");
	}

	void* Userdata = NewTypedUserdata(L, FVector_NetQuantizeNormal);
	new(Userdata) FVector_NetQuantizeNormal(*V);
	return 1;
}

static const luaL_Reg FVectorLib[] =
{
	{ "ToVector", FVector_ToVector },
	{ "ToVector2D", FVector_ToVector2D },
	{ "ToVector4", FVector_ToVector4 },
	{ "ToNetQuantize", FVector_ToNetQuantize },
	{ "ToNetQuantize10", FVector_ToNetQuantize10 },
	{ "ToNetQuantize100", FVector_ToNetQuantize100 },
	{ "ToNetQuantizeNormal", FVector_ToNetQuantizeNormal },
    { nullptr, nullptr }
};

BEGIN_EXPORT_CLASS_EX(true, FVector, UnLuaGame, FVector, nullptr)
    ADD_LIB(FVectorLib)
	ADD_FUNCTION(Equals)
	ADD_FUNCTION(IsZero)
	ADD_FUNCTION(IsNearlyZero)
END_EXPORT_CLASS()
IMPLEMENT_EXPORTED_CLASS_EX(FVector, UnLuaGame)
