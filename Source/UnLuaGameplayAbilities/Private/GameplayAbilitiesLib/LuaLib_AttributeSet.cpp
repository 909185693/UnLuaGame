// Copyright 2022 CQUnreal. All Rights Reserved.

#include "UnLuaEx.h"
#include "LuaCore.h"
#include "LuaDynamicBinding.h"
#include "AttributeSet.h"

/// <summary>
/// FGameplayAttribute
/// </summary>

static int32 FGameplayAttribute_New(lua_State* L)
{
	const int32 NumParams = lua_gettop(L);

	if (NumParams == 1)
	{
		void* Userdata = NewTypedUserdata(L, FGameplayAttribute);
		new(Userdata) FGameplayAttribute();
	}
	else if (NumParams == 2)
	{
		const char* FieldPath = lua_tostring(L, 2);
		if (!FieldPath)
		{
			return luaL_error(L, "invalid FieldPath!");
		}

		// Gather all UAttribute classes
		for (TObjectIterator<UClass> ClassIt; ClassIt; ++ClassIt)
		{
			UClass* Class = *ClassIt;
			if (Class->IsChildOf(UAttributeSet::StaticClass()))
			{
				for (TFieldIterator<FProperty> PropertyIt(Class, EFieldIteratorFlags::ExcludeSuper); PropertyIt; ++PropertyIt)
				{
					FProperty* Property = *PropertyIt;

					const FString PropertyPath = FString::Printf(TEXT("%s:%s"), *Class->GetFName().ToString(), *Property->GetFName().ToString());
					if (PropertyPath == UTF8_TO_TCHAR(FieldPath))
					{
						void* Userdata = NewTypedUserdata(L, FGameplayAttribute);
						new(Userdata) FGameplayAttribute(Property);
						return 1;
					}
				}
			}
		}
	}
	else
	{
		return luaL_error(L, "invalid parameters");
	}

	return luaL_error(L, "FGameplayAttribute not found!");
}

static const luaL_Reg FGameplayAttributeLib[] =
{
	{ "__call", FGameplayAttribute_New },
	{ nullptr, nullptr }
};

BEGIN_EXPORT_REFLECTED_CLASS(FGameplayAttribute)
	ADD_LIB(FGameplayAttributeLib)
END_EXPORT_CLASS()
IMPLEMENT_EXPORTED_CLASS(FGameplayAttribute)


/// <summary>
/// FGameplayAttributeDataLib
/// </summary>

static const luaL_Reg FGameplayAttributeDataLib[] =
{
    { nullptr, nullptr }
};

BEGIN_EXPORT_REFLECTED_CLASS(FGameplayAttributeData)
    ADD_CONST_FUNCTION_EX("GetCurrentValue", float, GetCurrentValue)
	ADD_FUNCTION_EX("SetCurrentValue", void, SetCurrentValue, float)
	ADD_CONST_FUNCTION_EX("GetBaseValue", float, GetBaseValue)
	ADD_FUNCTION_EX("SetBaseValue", void, SetBaseValue, float)
    ADD_LIB(FGameplayAttributeDataLib)
END_EXPORT_CLASS()
IMPLEMENT_EXPORTED_CLASS(FGameplayAttributeData)


/// <summary>
/// UAttributeSetLib
/// </summary>

static const luaL_Reg UAttributeSetLib[] =
{
	{ nullptr, nullptr }
};

BEGIN_EXPORT_REFLECTED_CLASS(UAttributeSet)
	ADD_LIB(UAttributeSetLib)
END_EXPORT_CLASS()
IMPLEMENT_EXPORTED_CLASS(UAttributeSet)
