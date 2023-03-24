// Copyright 2022 CQUnreal. All Rights Reserved.

#include "UnLuaEx.h"
#include "MathLib/LuaLib_Math.h"


static int32 FRotationTranslationMatrix_New(lua_State *L)
{
	int32 NumParams = lua_gettop(L);
	if (NumParams != 3)
	{
		return luaL_error(L, "invalid parameters");
	}

	void* Userdata = NewTypedUserdata(L, FRotationTranslationMatrix);
	FRotationTranslationMatrix* V = new(Userdata) FRotationTranslationMatrix(*((FRotator*)GetCppInstanceFast(L, 2)), *((FVector*)GetCppInstanceFast(L, 3)));
	return 1;
}

static int32 FRotationTranslationMatrix_ToMatrix(lua_State* L)
{
	int32 NumParams = lua_gettop(L);
	if (NumParams != 1)
	{
		return luaL_error(L, "invalid parameters");
	}

	void* Userdata = NewTypedUserdata(L, FMatrix);
	FMatrix* V = new(Userdata) FMatrix(*((FRotationTranslationMatrix*)GetCppInstanceFast(L, 1)));
	return 1;
}

static const luaL_Reg FRotationTranslationMatrixLib[] =
{
	{ "__tostring", UnLua::TMathUtils<FRotationTranslationMatrix>::ToString },
    { "__call", FRotationTranslationMatrix_New },
    { nullptr, nullptr }
};

BEGIN_EXPORT_CLASS_WITH_SUPER(FRotationTranslationMatrix, FMatrix, const FRotator&, const FVector&)
	ADD_CONST_FUNCTION_EX("__add", FMatrix, operator+, const FMatrix&)
	ADD_CONST_FUNCTION_EX("__mul", FMatrix, operator*, unluaReal)
	ADD_CONST_FUNCTION_EX("__mul", FMatrix, operator*, const FMatrix&)
	ADD_FUNCTION_EX("Add", void, operator+=, const FMatrix&)
	ADD_FUNCTION_EX("Mul", void, operator*=, unluaReal)
	ADD_FUNCTION_EX("Mul", void, operator*=, const FMatrix&)
    ADD_LIB(FRotationTranslationMatrixLib)
END_EXPORT_CLASS()
IMPLEMENT_EXPORTED_CLASS(FRotationTranslationMatrix)