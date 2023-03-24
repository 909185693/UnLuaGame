// Copyright 2022 CQUnreal. All Rights Reserved.

#include "UnLuaEx.h"
#include "UnLuaManager.h"
#include "LuaCore.h"

/**
 * Get the default object of UObject.
 */
static int32 UObject_GetDefaultObject(lua_State* L)
{
    int32 NumParams = lua_gettop(L);
    if (NumParams != 1)
    {
        return luaL_error(L, "invalid parameters");
    }

    UObject* Object = UnLua::GetUObject(L, 1);
    if (!Object)
	{
		return luaL_error(L, "invalid UObject");
    }

    UClass* Class = Cast<UClass>(Object);
    UObject* Ret = Class ? Class->GetDefaultObject() : Object->GetClass()->GetDefaultObject();
    if (Ret)
    {
        UnLua::PushUObject(L, Ret);
    }
    else
    {
        lua_pushnil(L);
    }

    return 1;
}

/**
 * Glue functions for UObject
 */
static const luaL_Reg UObjectLib[] =
{
	{ "GetDefaultObject", UObject_GetDefaultObject },
    { nullptr, nullptr }
};

/**
 * Export UObject
 */
BEGIN_EXPORT_CLASS_EX(true, UObject, UnLuaGame, UObject, nullptr)
    ADD_LIB(UObjectLib)
END_EXPORT_CLASS()
IMPLEMENT_EXPORTED_CLASS_EX(UObject, UnLuaGame)
