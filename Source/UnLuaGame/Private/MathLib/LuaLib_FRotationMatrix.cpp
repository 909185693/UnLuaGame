// Copyright 2022 CQUnreal. All Rights Reserved.

#include "UnLuaEx.h"
#include "MathLib/LuaLib_Math.h"


static int32 FRotationMatrix_New(lua_State* L)
{
	int32 NumParams = lua_gettop(L);
	if (NumParams != 2)
	{
		return luaL_error(L, "invalid parameters");
	}

	void* Userdata = NewTypedUserdata(L, FRotationMatrix);
	FRotationMatrix* V = new(Userdata) FRotationMatrix(*((FRotator*)GetCppInstanceFast(L, 2)));
	return 1;
}

static const luaL_Reg FRotationMatrixLib[] =
{
	{ "__tostring", UnLua::TMathUtils<FRotationMatrix>::ToString },
	{ "__call", FRotationMatrix_New },
	{ nullptr, nullptr }
};

BEGIN_EXPORT_CLASS_WITH_SUPER(FRotationMatrix, FRotationTranslationMatrix, const FRotator&)
	ADD_LIB(FRotationMatrixLib)
END_EXPORT_CLASS()
IMPLEMENT_EXPORTED_CLASS(FRotationMatrix)