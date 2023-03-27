// Copyright 2022 CQUnreal. All Rights Reserved.

#include "UnLuaEx.h"
#include "LuaCore.h"
#include "Misc/Base64.h"

static const luaL_Reg FBase64Lib[] =
{
	{ nullptr, nullptr }
};

BEGIN_EXPORT_CLASS(FBase64)
	ADD_STATIC_FUNCTION_EX("Encode", FString, Encode, const FString& /*Source*/)
	ADD_STATIC_FUNCTION_EX("Decode", bool, Decode, const FString& /*Source*/, FString& /*OutDest*/)
	ADD_LIB(FBase64Lib)
END_EXPORT_CLASS()
IMPLEMENT_EXPORTED_CLASS(FBase64)
