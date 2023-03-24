// Copyright 2022 CQUnreal. All Rights Reserved.

#include "UnLuaEx.h"
#include "LuaCore.h"
#include "LuaDynamicBinding.h"
#include "Engine/Texture.h"


static const luaL_Reg UTextureLib[] =
{
	{ nullptr, nullptr }
};

BEGIN_EXPORT_REFLECTED_CLASS(UTexture)
	ADD_STATIC_FUNCTION(ForceUpdateTextureStreaming)
    ADD_LIB(UTextureLib)
END_EXPORT_CLASS()
IMPLEMENT_EXPORTED_CLASS(UTexture)
