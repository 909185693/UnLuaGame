// Copyright 2022 CQUnreal. All Rights Reserved.

#include "UnLuaEx.h"
#include "LuaCore.h"
#include "Math/Plane.h"

static int32 FPlane_New(lua_State *L)
{
	int32 NumParams = lua_gettop(L);
	void *Userdata = NewTypedUserdata(L, FPlane);
	FPlane* Plane = nullptr;
	if (NumParams == 4)
	{
		Plane = new(Userdata) FPlane(*(FVector*)GetCppInstanceFast(L, 2), *(FVector*)GetCppInstanceFast(L, 3), *(FVector*)GetCppInstanceFast(L, 4));
	}
	return 1;
}

static const luaL_Reg FPlaneLib[] =
{
	{ "__call", FPlane_New },
	{ nullptr, nullptr }
};

BEGIN_EXPORT_REFLECTED_CLASS(FPlane)
ADD_LIB(FPlaneLib)
END_EXPORT_CLASS()
IMPLEMENT_EXPORTED_CLASS(FPlane)
