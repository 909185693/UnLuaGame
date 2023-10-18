// Copyright 2022 CQUnreal. All Rights Reserved.

#include "UnLuaEx.h"
#include "LuaCore.h"
#include "GameplayTagContainer.h"

static int32 FGameplayTag_New(lua_State *L)
{
	void *Userdata = NewTypedUserdata(L, FGameplayTag);
	new(Userdata) FGameplayTag();

	int32 NumParams = lua_gettop(L);
	if (NumParams > 1)
	{
		*(FGameplayTag*)(Userdata) = FGameplayTag::RequestGameplayTag(lua_tostring(L, 2));
	}

	return 1;
}

static const luaL_Reg FGameplayTagLib[] =
{
	{ "__call", FGameplayTag_New },
	{ nullptr, nullptr }
};

BEGIN_EXPORT_REFLECTED_CLASS(FGameplayTag)
	ADD_CONST_FUNCTION_EX("__eq", bool, operator==, FGameplayTag const&)
	ADD_FUNCTION(MatchesTag)
	ADD_FUNCTION(MatchesTagExact)
	ADD_FUNCTION(MatchesTagDepth)
	ADD_FUNCTION(MatchesAny)
	ADD_FUNCTION(MatchesAnyExact)
	ADD_FUNCTION(GetSingleTagContainer)
	ADD_FUNCTION(RequestDirectParent)
	ADD_FUNCTION(GetGameplayTagParents)
	ADD_FUNCTION(ToString)
	ADD_FUNCTION(GetTagName)
	ADD_LIB(FGameplayTagLib)
END_EXPORT_CLASS()
IMPLEMENT_EXPORTED_CLASS(FGameplayTag)


static int32 FGameplayTagContainer_New(lua_State* L)
{
	int32 NumParams = lua_gettop(L);
	if (NumParams > 1)
	{
		TArray<FGameplayTag> GameplayTags;

		int Size = lua_rawlen(L, 2);
		for (int i = 1; i <= Size; i++)
		{
			lua_pushstring(L, nullptr);
			//lua_gettable(L, 2);
			lua_rawgeti(L, 2, i);

			FGameplayTag GameplayTag = FGameplayTag::RequestGameplayTag(lua_tostring(L, -1));
			if (GameplayTag.IsValid())
			{
				GameplayTags.Add(GameplayTag);
			}

			lua_pop(L, 1);
		};

		void* Userdata = NewTypedUserdata(L, FGameplayTagContainer);
		new(Userdata) FGameplayTagContainer(FGameplayTagContainer::CreateFromArray(GameplayTags));
	}
	else
	{
		void* Userdata = NewTypedUserdata(L, FGameplayTagContainer);
		new(Userdata) FGameplayTagContainer();
	}

	return 1;
}

static const luaL_Reg FGameplayTagContainerLib[] =
{
	{ "__call", FGameplayTagContainer_New },
	{ nullptr, nullptr }
};

BEGIN_EXPORT_REFLECTED_CLASS(FGameplayTagContainer)
	ADD_CONST_FUNCTION_EX("HasTag", bool, HasTag, FGameplayTag const&)
	ADD_FUNCTION(HasTagExact)
	ADD_FUNCTION(HasAny)
	ADD_FUNCTION(HasAnyExact)
	ADD_FUNCTION(HasAll)
	ADD_FUNCTION(HasAllExact)
	ADD_FUNCTION(Num)
	ADD_FUNCTION(IsValid)
	ADD_FUNCTION(IsEmpty)
	ADD_FUNCTION(GetGameplayTagParents)
//	ADD_FUNCTION(Filter)
	ADD_FUNCTION(FilterExact)
	ADD_FUNCTION(MatchesQuery)
	ADD_FUNCTION(AppendTags)
	ADD_FUNCTION(AppendMatchingTags)
	ADD_FUNCTION(AddTag)
	ADD_FUNCTION(AddTagFast)
	ADD_FUNCTION(AddLeafTag)
	ADD_FUNCTION(RemoveTag)
	ADD_FUNCTION(RemoveTags)
	ADD_FUNCTION(Reset)
	ADD_FUNCTION(ToString)
#if ENGINE_MAJOR_VERSION >= 5 && ENGINE_MINOR_VERSION >= 3
	ADD_CONST_FUNCTION_EX("GetGameplayTagArray", const TArray<FGameplayTag>&, GetGameplayTagArray)
#else
	ADD_FUNCTION(GetGameplayTagArray)
#endif
	ADD_LIB(FGameplayTagContainerLib)
END_EXPORT_CLASS()
IMPLEMENT_EXPORTED_CLASS(FGameplayTagContainer)
