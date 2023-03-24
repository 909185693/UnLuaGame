// Copyright 2022 CQUnreal. All Rights Reserved.

#include "UnLuaEx.h"
#include "LuaCore.h"
#include "LuaDynamicBinding.h"
#include "Components/SceneComponent.h"


static const luaL_Reg USceneComponentLib[] =
{
	{ nullptr, nullptr }
};

// Export Actor Component
BEGIN_EXPORT_REFLECTED_CLASS(USceneComponent)
	ADD_FUNCTION(ShouldRender)
	ADD_FUNCTION(CanEverRender)
	ADD_LIB(USceneComponentLib)
END_EXPORT_CLASS()
IMPLEMENT_EXPORTED_CLASS(USceneComponent)

