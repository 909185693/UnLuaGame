// Copyright 2022 CQUnreal. All Rights Reserved.

#include "UnLuaEx.h"
#include "LuaCore.h"
#include "Misc/Timespan.h"

static int32 FTimespan_New(lua_State *L)
{
	const int32 NumParams = lua_gettop(L);
	void* Userdata = NewTypedUserdata(L, FTimespan);

	switch (NumParams)
	{
	case 4:
		new(Userdata) FTimespan(lua_tointeger(L, 2), lua_tointeger(L, 3), lua_tointeger(L, 4));
		break;
	case 5:
		new(Userdata) FTimespan(lua_tointeger(L, 2), lua_tointeger(L, 3), lua_tointeger(L, 4), lua_tointeger(L, 5));
		break;
	case 6:
		new(Userdata) FTimespan(lua_tointeger(L, 2), lua_tointeger(L, 3), lua_tointeger(L, 4), lua_tointeger(L, 5), lua_tointeger(L, 6));
		break;
	default:
		return luaL_error(L, "invalid parameters");
	}
	
	return 1;
}

static const luaL_Reg FTimespanLib[] =
{
	{ "__call", FTimespan_New },
	{ nullptr, nullptr }
};

BEGIN_EXPORT_REFLECTED_CLASS(FTimespan)
	ADD_FUNCTION(GetDays)
	ADD_FUNCTION(GetHours)
	ADD_FUNCTION(GetMinutes)
	ADD_FUNCTION(GetSeconds)
	ADD_LIB(FTimespanLib)
END_EXPORT_CLASS()
IMPLEMENT_EXPORTED_CLASS(FTimespan)
