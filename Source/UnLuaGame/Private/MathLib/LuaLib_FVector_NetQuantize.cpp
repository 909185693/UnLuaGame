// Copyright 2022 CQUnreal. All Rights Reserved.

#include "UnLuaEx.h"
#include "MathLib/LuaLib_Math.h"

static int32 FVector_NetQuantize_New(lua_State* L)
{
	int32 NumParams = lua_gettop(L);
	void* Userdata = NewTypedUserdata(L, FVector_NetQuantize);
	FVector_NetQuantize* V = new(Userdata) FVector_NetQuantize(EForceInit::ForceInitToZero);
	UnLua::TFieldSetter3<unluaReal>::Set(L, NumParams, &V->X);

	return 1;
}

static const luaL_Reg FVector_NetQuantizeLib[] =
{
	{ "__tostring", UnLua::TMathUtils<FVector_NetQuantize>::ToString },
	{ "__call", FVector_NetQuantize_New },
	{ nullptr, nullptr }
};

BEGIN_EXPORT_REFLECTED_CLASS(FVector_NetQuantize)
	ADD_LIB(FVector_NetQuantizeLib)
END_EXPORT_CLASS()
IMPLEMENT_EXPORTED_CLASS(FVector_NetQuantize)
