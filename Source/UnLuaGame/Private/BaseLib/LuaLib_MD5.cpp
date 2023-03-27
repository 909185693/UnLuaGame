// Copyright 2022 CQUnreal. All Rights Reserved.

#include "UnLuaEx.h"
#include "LuaCore.h"
#include "Misc/SecureHash.h"

static const luaL_Reg FMD5Lib[] =
{
	{ nullptr, nullptr }
};

FString HashAnsiString(const FString& String)
{
	return FMD5::HashAnsiString(*String);
}

BEGIN_EXPORT_CLASS(FMD5)
	ADD_EXTERNAL_FUNCTION(FString, HashAnsiString, const FString& /*String*/)
	ADD_LIB(FMD5Lib)
END_EXPORT_CLASS()
IMPLEMENT_EXPORTED_CLASS(FMD5)
