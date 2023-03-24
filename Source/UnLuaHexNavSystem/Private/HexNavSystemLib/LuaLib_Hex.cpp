// Copyright 2022 CQUnreal. All Rights Reserved.

#include "UnLuaEx.h"
#include "LuaCore.h"
#include "LuaDynamicBinding.h"
#include "HexGenerator.h"

BEGIN_EXPORT_ENUM(EHexFlag)
	ADD_ENUM_VALUE(Occupied)
	ADD_ENUM_VALUE(NoCreated)
	ADD_ENUM_VALUE(NoMoved)
	ADD_ENUM_VALUE(NoInfantry)
	ADD_ENUM_VALUE(NoVehicle)
	ADD_ENUM_VALUE(NoAircraft)
END_EXPORT_ENUM(EHexFlag)

static const luaL_Reg FHexLib[] =
{
    { nullptr, nullptr }
};

BEGIN_EXPORT_REFLECTED_CLASS(FHex)
	ADD_FUNCTION(IsValid)
	ADD_FUNCTION(HasPlaceActor)
	ADD_FUNCTION(GetOccupyActor)
	ADD_FUNCTION_EX("HasAnyFlags", bool, HasAnyFlags, EHexFlag)
	ADD_FUNCTION_EX("HasAllFlags", bool, HasAllFlags, EHexFlag)
	ADD_STATIC_FUNCTION_EX("HasAnyFlags", bool, HasAnyFlags, EHexFlag, EHexFlag)
	ADD_STATIC_FUNCTION_EX("HasAllFlags", bool, HasAllFlags, EHexFlag, EHexFlag)
	ADD_STATIC_FUNCTION(MakeVertices)
	ADD_STATIC_FUNCTION(MakeTriangles)
	ADD_LIB(FHexLib)
END_EXPORT_CLASS()
IMPLEMENT_EXPORTED_CLASS(FHex)

static const luaL_Reg FHexHandleLib[] =
{
    { nullptr, nullptr }
};

BEGIN_EXPORT_REFLECTED_CLASS(FHexHandle)
	ADD_FUNCTION(IsValid)
	ADD_FUNCTION(Get)
	ADD_FUNCTION(Reset)
	ADD_FUNCTION(GetSectionIndex)
	ADD_FUNCTION(GetPlaceActors)
	ADD_FUNCTION(HasPlaceActor)
	ADD_FUNCTION(GetOccupyActor)
	ADD_FUNCTION(GetWorldLocation)
	ADD_FUNCTION(GetCoordinate)
	ADD_FUNCTION(GetFlags)
	ADD_FUNCTION(HasAnyFlags)
	ADD_FUNCTION(HasAllFlags)
	ADD_LIB(FHexHandleLib)
END_EXPORT_CLASS()
IMPLEMENT_EXPORTED_CLASS(FHexHandle)

