// Copyright 2022 CQUnreal. All Rights Reserved.

#include "InputCoreTypes.h"
#include "UnLuaEx.h"
#include "LuaCore.h"

static int32 FKey_New(lua_State* L)
{
    void* Userdata = NewTypedUserdata(L, FKey);

    int32 NumParams = lua_gettop(L);
    if (NumParams > 1)
    {
        new(Userdata) FKey(lua_tostring(L, 2));
    }
    else
    {
        new(Userdata) FKey();
    }

    return 1;
}

static const luaL_Reg FKeyLib[] =
{
    { "__call", FKey_New },
    { nullptr, nullptr }
};

/**
 * Export FKey
 */
BEGIN_EXPORT_REFLECTED_CLASS(FKey)
    ADD_LIB(FKeyLib)
END_EXPORT_CLASS()
IMPLEMENT_EXPORTED_CLASS(FKey)