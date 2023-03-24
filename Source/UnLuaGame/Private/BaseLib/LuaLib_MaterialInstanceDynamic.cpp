// Copyright 2022 CQUnreal. All Rights Reserved.

#include "UnLuaEx.h"
#include "LuaCore.h"
#include "LuaDynamicBinding.h"
#include "Materials/MaterialInstanceDynamic.h"


static int32 UMaterialInstanceDynamic_Create(lua_State* L)
{
	int32 NumParams = lua_gettop(L);
	if (NumParams < 2)
	{
		return luaL_error(L, "invalid parameters");
	}

	UMaterialInterface* MaterialInterface = Cast<UMaterialInterface>(UnLua::GetUObject(L, 1));
	if (!MaterialInterface)
	{
		return luaL_error(L, "invalid UMaterialInterface");
	}

	UObject* Object = UnLua::GetUObject(L, 2);

	UMaterialInstanceDynamic* MaterialInstanceDynamic = UMaterialInstanceDynamic::Create(MaterialInterface, Object);
	UnLua::PushUObject(L, MaterialInstanceDynamic);

	return 1;
}


static const luaL_Reg UMaterialInstanceDynamicLib[] =
{
	{ "Create", UMaterialInstanceDynamic_Create },
	{ nullptr, nullptr }
};

BEGIN_EXPORT_CLASS_EX(true, UMaterialInstanceDynamic, UnLuaGame, UMaterialInstanceDynamic, nullptr)
    ADD_LIB(UMaterialInstanceDynamicLib)
END_EXPORT_CLASS()
IMPLEMENT_EXPORTED_CLASS_EX(UMaterialInstanceDynamic, UnLuaGame)
