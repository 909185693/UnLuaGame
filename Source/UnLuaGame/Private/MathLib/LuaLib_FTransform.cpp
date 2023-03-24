// Copyright 2022 CQUnreal. All Rights Reserved.

#include "UnLuaEx.h"
#include "MathLib/LuaLib_Math.h"

static int32 FTransform_ToMatrixWithScale(lua_State* L)
{
	int32 NumParams = lua_gettop(L);
	if (NumParams != 1)
	{
		return luaL_error(L, "invalid parameters");
	}

	FTransform* Transform = (FTransform*)GetCppInstanceFast(L, 1);
	if (!Transform)
	{
		return luaL_error(L, "invalid FTransform");
	}

	void* Userdata = NewTypedUserdata(L, FMatrix);
	FMatrix* V = new(Userdata) FMatrix(Transform->ToMatrixWithScale());
	return 1;
}

static int32 FTransform_ToMatrixNoScale(lua_State* L)
{
	int32 NumParams = lua_gettop(L);
	if (NumParams != 1)
	{
		return luaL_error(L, "invalid parameters");
	}

	FTransform* Transform = (FTransform*)GetCppInstanceFast(L, 1);
	if (!Transform)
	{
		return luaL_error(L, "invalid FTransform");
	}

	void* Userdata = NewTypedUserdata(L, FMatrix);
	FMatrix* V = new(Userdata) FMatrix(Transform->ToMatrixNoScale());
	return 1;
}

static int32 FTransform_ToInverseMatrixWithScale(lua_State* L)
{
	int32 NumParams = lua_gettop(L);
	if (NumParams != 1)
	{
		return luaL_error(L, "invalid parameters");
	}

	FTransform* Transform = (FTransform*)GetCppInstanceFast(L, 1);
	if (!Transform)
	{
		return luaL_error(L, "invalid FTransform");
	}

	void* Userdata = NewTypedUserdata(L, FMatrix);
	FMatrix* V = new(Userdata) FMatrix(Transform->ToInverseMatrixWithScale());
	return 1;
}

static const luaL_Reg FTransformLib[] =
{
	{"ToMatrixWithScale", FTransform_ToMatrixWithScale },
	{"ToMatrixNoScale", FTransform_ToMatrixNoScale },
	{"ToInverseMatrixWithScale", FTransform_ToInverseMatrixWithScale },
    {nullptr, nullptr}
};

BEGIN_EXPORT_CLASS_EX(true, FTransform, UnLuaGame, FTransform, nullptr)
	ADD_FUNCTION(GetLocation)
	ADD_NAMED_FUNCTION("GetRotator", Rotator)
    ADD_LIB(FTransformLib)
END_EXPORT_CLASS()
IMPLEMENT_EXPORTED_CLASS_EX(FTransform, UnLuaGame)
