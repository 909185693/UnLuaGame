// Copyright 2022 CQUnreal. All Rights Reserved.

#include "UnLuaEx.h"
#include "MathLib/LuaLib_Math.h"

static int32 FVector_NetQuantizeNormal_New(lua_State* L)
{
	int32 NumParams = lua_gettop(L);
	void* Userdata = NewTypedUserdata(L, FVector_NetQuantizeNormal);
	FVector_NetQuantizeNormal* V = new(Userdata) FVector_NetQuantizeNormal(EForceInit::ForceInitToZero);
	UnLua::TFieldSetter3<unluaReal>::Set(L, NumParams, &V->X);

	return 1;
}

static const luaL_Reg FVector_NetQuantizeNormalLib[] =
{
	{ "__tostring", UnLua::TMathUtils<FVector_NetQuantizeNormal>::ToString },
	{ "__call", FVector_NetQuantizeNormal_New },
	{ nullptr, nullptr }
};

BEGIN_EXPORT_REFLECTED_CLASS(FVector_NetQuantizeNormal)
	ADD_LIB(FVector_NetQuantizeNormalLib)
END_EXPORT_CLASS()
IMPLEMENT_EXPORTED_CLASS(FVector_NetQuantizeNormal)
