// Copyright 2022 CQUnreal. All Rights Reserved.

#include "UnLuaEx.h"
#include "LuaCore.h"
#include "LuaDynamicBinding.h"

#if ENGINE_MAJOR_VERSION > 4
#include "InputActionValue.h"


static int32 FInputActionValue_New(lua_State* L)
{
	const int32 NumParams = lua_gettop(L);

	if (NumParams != 2)
	{
		return luaL_error(L, "invalid parameters");
	}

	void* Userdata = NewTypedUserdata(L, FInputActionValue);

	FVector* V = (FVector*)GetCppInstanceFast(L, 2);
	new(Userdata)FInputActionValue(*V);

	return 1;
}

static int32 FInputActionValue_GetAxis1D(lua_State *L)
{
	int32 NumParams = lua_gettop(L);
	if (NumParams != 1)
	{
		return luaL_error(L, "invalid parameters");
	}

	FInputActionValue* InputActionValue = (FInputActionValue*)GetCppInstanceFast(L, 1);
	if (!InputActionValue)
	{
		return luaL_error(L, "invalid FInputActionValue");
	}

	lua_pushnumber(L, InputActionValue->Get<FInputActionValue::Axis1D>());
	
	return 1;
}

static int32 FInputActionValue_GetAxis2D(lua_State* L)
{
	int32 NumParams = lua_gettop(L);
	if (NumParams != 1)
	{
		return luaL_error(L, "invalid parameters");
	}

	FInputActionValue* InputActionValue = (FInputActionValue*)GetCppInstanceFast(L, 1);
	if (!InputActionValue)
	{
		return luaL_error(L, "invalid FInputActionValue");
	}

	void* Userdata = NewTypedUserdata(L, FVector2D);
	new(Userdata) FVector2D(InputActionValue->Get<FInputActionValue::Axis2D>());

	return 1;
}

static int32 FInputActionValue_GetAxis3D(lua_State* L)
{
	int32 NumParams = lua_gettop(L);
	if (NumParams != 1)
	{
		return luaL_error(L, "invalid parameters");
	}

	FInputActionValue* InputActionValue = (FInputActionValue*)GetCppInstanceFast(L, 1);
	if (!InputActionValue)
	{
		return luaL_error(L, "invalid FInputActionValue");
	}

	void* Userdata = NewTypedUserdata(L, FVector);
	new(Userdata) FVector(InputActionValue->Get<FInputActionValue::Axis3D>());

	return 1;
}

static const luaL_Reg FInputActionValuLib[] =
{
	{ "GetAxis1D", FInputActionValue_GetAxis1D },
	{ "GetAxis2D", FInputActionValue_GetAxis2D },
	{ "GetAxis3D", FInputActionValue_GetAxis3D },
	{"__call", FInputActionValue_New},
    { nullptr, nullptr }
};

BEGIN_EXPORT_REFLECTED_CLASS(FInputActionValue)
	ADD_LIB(FInputActionValuLib)
END_EXPORT_CLASS()
IMPLEMENT_EXPORTED_CLASS(FInputActionValue)

#endif