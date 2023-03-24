// Copyright 2022 CQUnreal. All Rights Reserved.

#include "UnLuaEx.h"
#include "MathLib/LuaLib_Math.h"


static const luaL_Reg FRotatorLib[] =
{
    {nullptr, nullptr}
};

BEGIN_EXPORT_CLASS_EX(true, FRotator, UnLuaGame, FRotator, nullptr)
    ADD_LIB(FRotatorLib)
	ADD_FUNCTION(Equals)
	ADD_FUNCTION(RotateVector)
END_EXPORT_CLASS()
IMPLEMENT_EXPORTED_CLASS_EX(FRotator, UnLuaGame)
