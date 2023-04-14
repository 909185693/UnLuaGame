// Copyright 2022 CQUnreal. All Rights Reserved.

#include "InputCoreTypes.h"
#include "UnLuaEx.h"
#include "LuaCore.h"


static int32 FUniqueNetIdRepl_Eq(lua_State* L)
{
	int32 NumParams = lua_gettop(L);
	if (NumParams != 2)
		return luaL_error(L, "invalid parameters");

	FUniqueNetIdRepl* Lhs = (FUniqueNetIdRepl*)GetCppInstanceFast(L, 1);
	if (!Lhs)
		return luaL_error(L, "invalid FUniqueNetIdRepl");

	FUniqueNetIdRepl* Rhs = (FUniqueNetIdRepl*)GetCppInstanceFast(L, 2);
	if (Rhs != nullptr)
	{
		bool bResult = (*Lhs == *Rhs);
		lua_pushboolean(L, bResult);
	}
	else
	{
		lua_pushboolean(L, false);
	}

	return 1;
}

static const luaL_Reg FUniqueNetIdReplLib[] =
{
    { "__eq", FUniqueNetIdRepl_Eq },
    { nullptr, nullptr }
};


/**
 * Export FUniqueNetIdRepl
 */
BEGIN_EXPORT_REFLECTED_CLASS(FUniqueNetIdRepl)
	ADD_FUNCTION_EX("ToString", FString, ToString)
	ADD_FUNCTION_EX("__tostring", FString, ToString)
    ADD_LIB(FUniqueNetIdReplLib)
END_EXPORT_CLASS()
IMPLEMENT_EXPORTED_CLASS(FUniqueNetIdRepl)