// Copyright 2022 CQUnreal. All Rights Reserved.

#include "UnLuaEx.h"
#include "LuaCore.h"
#include "LuaDynamicBinding.h"
#include "GameFramework/NavMovementComponent.h"


static const luaL_Reg UNavMovementComponentLib[] =
{
	{ nullptr, nullptr }
};

// Export Actor Component
BEGIN_EXPORT_REFLECTED_CLASS(UNavMovementComponent)
	ADD_FUNCTION(GetActorFeetLocation)
	ADD_LIB(UNavMovementComponentLib)
END_EXPORT_CLASS()
IMPLEMENT_EXPORTED_CLASS(UNavMovementComponent)

