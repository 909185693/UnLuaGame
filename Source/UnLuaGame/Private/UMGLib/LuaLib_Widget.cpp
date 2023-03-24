// Copyright 2022 CQUnreal. All Rights Reserved.

#include "UnLuaEx.h"
#include "LuaCore.h"
#include "LuaDynamicBinding.h"
#include "Components/Widget.h"

static int32 UWidget_IsDirectlyHovered(lua_State* L)
{
	int32 NumParams = lua_gettop(L);
	if (NumParams != 1)
	{
		return luaL_error(L, "invalid parameters");
	}

	UWidget* Widget = Cast<UWidget>(UnLua::GetUObject(L, 1));
	if (!Widget)
	{
		return luaL_error(L, "invalid UWidget");
	}
	
	TSharedPtr<SWidget> SafeWidget = Widget->GetCachedWidget();
	if (SafeWidget.IsValid())
	{
		lua_pushboolean(L, SafeWidget->IsDirectlyHovered());
		return 1;
	}

	lua_pushboolean(L, 0);
	return 1;
}

static const luaL_Reg UWidgetLib[] =
{
	{ "IsDirectlyHovered", UWidget_IsDirectlyHovered },
    { nullptr, nullptr }
};

BEGIN_EXPORT_REFLECTED_CLASS(UWidget)
	ADD_LIB(UWidgetLib)
END_EXPORT_CLASS()
IMPLEMENT_EXPORTED_CLASS(UWidget)
