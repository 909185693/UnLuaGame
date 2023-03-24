// Copyright 2022 CQUnreal. All Rights Reserved.

#include "Http.h"
#include "HttpRequest.h"
#include "UnLuaEx.h"
#include "LuaCore.h"


static const luaL_Reg FHttpModuleLib[] =
{
	{ nullptr, nullptr }
};

class FHttpModuleEx
{
public:
    static UHttpRequest* CreateRequest()
    {
        return UHttpRequest::Create();
    }
};

BEGIN_EXPORT_NAMED_CLASS(FHttpModule, FHttpModuleEx)
    ADD_STATIC_FUNCTION(CreateRequest)
    ADD_LIB(FHttpModuleLib)
END_EXPORT_CLASS()
IMPLEMENT_EXPORTED_CLASS(FHttpModule)
