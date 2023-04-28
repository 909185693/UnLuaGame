// Copyright 2022 CQUnreal. All Rights Reserved.

#include "UnLuaEx.h"
#include "LuaCore.h"
#include "LuaDynamicBinding.h"
#include "BehaviorTree/BehaviorTreeComponent.h"


BEGIN_EXPORT_ENUM_EX(EBTStopMode::Type, EBTStopMode)
	ADD_SCOPED_ENUM_VALUE(Safe)
	ADD_SCOPED_ENUM_VALUE(Forced)
END_EXPORT_ENUM(EBTStopMode)

static const luaL_Reg UBehaviorTreeComponentLib[] =
{
	{ nullptr, nullptr }
};

// Export Actor Component
BEGIN_EXPORT_REFLECTED_CLASS(UBehaviorTreeComponent)
	ADD_FUNCTION(StopTree)
	ADD_LIB(UBehaviorTreeComponentLib)
END_EXPORT_CLASS()
IMPLEMENT_EXPORTED_CLASS(UBehaviorTreeComponent)

