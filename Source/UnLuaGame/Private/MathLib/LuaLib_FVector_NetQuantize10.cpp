// Copyright 2022 CQUnreal. All Rights Reserved.

#include "UnLuaEx.h"
#include "MathLib/LuaLib_Math.h"

static int32 FVector_NetQuantize10_New(lua_State* L)
{
	int32 NumParams = lua_gettop(L);
	void* Userdata = NewTypedUserdata(L, FVector_NetQuantize10);
	FVector_NetQuantize10* V = new(Userdata) FVector_NetQuantize10(EForceInit::ForceInitToZero);
	UnLua::TFieldSetter3<unluaReal>::Set(L, NumParams, &V->X);

	return 1;
}

static const luaL_Reg FVector_NetQuantize10Lib[] =
{
	{ "__tostring", UnLua::TMathUtils<FVector_NetQuantize10>::ToString },
	{ "__call", FVector_NetQuantize10_New },
	{ nullptr, nullptr }
};

BEGIN_EXPORT_REFLECTED_CLASS(FVector_NetQuantize10)
	ADD_LIB(FVector_NetQuantize10Lib)
END_EXPORT_CLASS()
IMPLEMENT_EXPORTED_CLASS(FVector_NetQuantize10)
