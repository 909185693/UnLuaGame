// Copyright 2022 CQUnreal. All Rights Reserved.

#include "UnLuaEx.h"
#include "LuaCore.h"
#include "LuaDynamicBinding.h"
#include "Math/Axis.h"
#include "Engine/EngineBaseTypes.h"


BEGIN_EXPORT_ENUM_EX(ENetMode, ENetMode)
	ADD_SCOPED_ENUM_VALUE(NM_Standalone)
	ADD_SCOPED_ENUM_VALUE(NM_DedicatedServer)
	ADD_SCOPED_ENUM_VALUE(NM_ListenServer)
	ADD_SCOPED_ENUM_VALUE(NM_Client)
END_EXPORT_ENUM(ENetMode)

BEGIN_EXPORT_ENUM_EX(EAxis::Type, EAxis)
	ADD_SCOPED_ENUM_VALUE(None)
	ADD_SCOPED_ENUM_VALUE(X)
	ADD_SCOPED_ENUM_VALUE(Y)
	ADD_SCOPED_ENUM_VALUE(Z)
END_EXPORT_ENUM(EAxis)



