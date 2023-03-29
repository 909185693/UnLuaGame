// Copyright 2022 CQUnreal. All Rights Reserved.

#include "UnLuaEx.h"
#include "LuaCore.h"
#include "Misc/Base64.h"

static const luaL_Reg FBase64Lib[] =
{
	{ nullptr, nullptr }
};

#if ENGINE_MAJOR_VERSION >= 5 && ENGINE_MINOR_VERSION >= 2
BEGIN_EXPORT_ENUM(EBase64Mode)
	ADD_SCOPED_ENUM_VALUE(Standard)
	ADD_SCOPED_ENUM_VALUE(UrlSafe)
END_EXPORT_ENUM(EBase64Mode)
#endif

BEGIN_EXPORT_CLASS(FBase64)
#if ENGINE_MAJOR_VERSION >= 5 && ENGINE_MINOR_VERSION >= 2
	ADD_STATIC_FUNCTION_EX("Encode", FString, Encode, const FString& /*Source*/, EBase64Mode /*Mode = EBase64Mode::Standard*/)
	ADD_STATIC_FUNCTION_EX("Decode", bool, Decode, const FString& /*Source*/, FString& /*OutDest*/, EBase64Mode /*Mode = EBase64Mode::Standard*/)
#else
	ADD_STATIC_FUNCTION_EX("Encode", FString, Encode, const FString& /*Source*/)
	ADD_STATIC_FUNCTION_EX("Decode", bool, Decode, const FString& /*Source*/, FString& /*OutDest*/)
#endif
	ADD_LIB(FBase64Lib)
END_EXPORT_CLASS()
IMPLEMENT_EXPORTED_CLASS(FBase64)
