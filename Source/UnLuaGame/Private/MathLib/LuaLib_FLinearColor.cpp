// Copyright 2022 CQUnreal. All Rights Reserved.

#include "UnLuaEx.h"
#include "MathLib/LuaLib_Math.h"

static const luaL_Reg FLinearColorLib[] =
{
    {nullptr, nullptr}
};

BEGIN_EXPORT_CLASS_EX(true, FLinearColor, UnLuaGame, FLinearColor, nullptr)
    ADD_LIB(FLinearColorLib)
    ADD_STATIC_PROPERTY(Gray)
    ADD_STATIC_PROPERTY(Transparent)
    ADD_STATIC_PROPERTY(Red)
	ADD_STATIC_PROPERTY(Green)
	ADD_STATIC_PROPERTY(Blue)
	ADD_STATIC_PROPERTY(Yellow)
END_EXPORT_CLASS()
IMPLEMENT_EXPORTED_CLASS_EX(FLinearColor, UnLuaGame)
