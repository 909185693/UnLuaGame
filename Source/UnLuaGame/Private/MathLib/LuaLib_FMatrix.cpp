// Copyright 2022 CQUnreal. All Rights Reserved.

#include "UnLuaEx.h"
#include "MathLib/LuaLib_Math.h"

static int32 FMatrix_New(lua_State* L)
{
	int32 NumParams = lua_gettop(L);
	void* Userdata = NewTypedUserdata(L, FMatrix);
	FMatrix* V = new(Userdata) FMatrix();
	return 1;
}

static const luaL_Reg FMatrixLib[] =
{
	{ "__tostring", UnLua::TMathUtils<FMatrix>::ToString },
	{ "__call", FMatrix_New },
	{ nullptr, nullptr }
};

BEGIN_EXPORT_CLASS(FMatrix)
	ADD_FUNCTION(SetIdentity)
	//ADD_FUNCTION(Equals)
	ADD_FUNCTION(TransformFVector4)
	ADD_FUNCTION(TransformPosition)
	ADD_FUNCTION(InverseTransformPosition)
	ADD_FUNCTION(TransformVector)
	ADD_FUNCTION(InverseTransformVector)
	ADD_FUNCTION(GetTransposed)
	ADD_FUNCTION(Determinant)
	ADD_FUNCTION(RotDeterminant)
	ADD_FUNCTION(InverseFast)
	ADD_FUNCTION(Inverse)
	ADD_FUNCTION(TransposeAdjoint)
	ADD_FUNCTION(RemoveScaling)
	ADD_FUNCTION(GetMatrixWithoutScale)
	ADD_FUNCTION(ExtractScaling)
	ADD_FUNCTION(GetScaleVector)
	ADD_FUNCTION(RemoveTranslation)
	ADD_FUNCTION(ConcatTranslation)
	ADD_FUNCTION(ContainsNaN)
	ADD_FUNCTION(ScaleTranslation)
	ADD_FUNCTION(GetMaximumAxisScale)
	ADD_FUNCTION(ApplyScale)
	ADD_FUNCTION(GetOrigin)
	ADD_FUNCTION(GetScaledAxis)
	ADD_FUNCTION(GetScaledAxes)
	ADD_FUNCTION(GetUnitAxis)
	ADD_FUNCTION(GetUnitAxes)
	ADD_FUNCTION(SetAxis)
	ADD_FUNCTION(SetOrigin)
	//ADD_FUNCTION(SetAxes)
	ADD_FUNCTION(GetColumn)
	ADD_FUNCTION(SetColumn)
	ADD_FUNCTION(Rotator)
	ADD_FUNCTION(ToQuat)
	ADD_FUNCTION(GetFrustumNearPlane)
	ADD_FUNCTION(GetFrustumFarPlane)
	ADD_FUNCTION(GetFrustumLeftPlane)
	ADD_FUNCTION(GetFrustumRightPlane)
	ADD_FUNCTION(GetFrustumTopPlane)
	ADD_FUNCTION(GetFrustumBottomPlane)
	ADD_FUNCTION(Mirror)
	//ADD_FUNCTION(DebugPrint)
	ADD_FUNCTION(ComputeHash)
	ADD_CONST_FUNCTION_EX("__add", FMatrix, operator+, const FMatrix&)
	ADD_CONST_FUNCTION_EX("__mul", FMatrix, operator*, unluaReal)
    ADD_CONST_FUNCTION_EX("__mul", FMatrix, operator*, const FMatrix&)
	ADD_FUNCTION_EX("Add", void, operator+=, const FMatrix&)
	ADD_FUNCTION_EX("Mul", void, operator*=, unluaReal)
    ADD_FUNCTION_EX("Mul", void, operator*=, const FMatrix&)
    ADD_LIB(FMatrixLib)
END_EXPORT_CLASS()
IMPLEMENT_EXPORTED_CLASS(FMatrix)