// Copyright 2022 CQUnreal. All Rights Reserved.

#include "UnLuaEnhancedInputPrivate.h"
#include "Modules/ModuleManager.h"

class FUnLuaEnhancedInputModule : public IModuleInterface
{
public:
	/** IModuleInterface implementation */
	virtual void StartupModule() override
	{

	}

	virtual void ShutdownModule() override
	{

	}
};

IMPLEMENT_MODULE(FUnLuaEnhancedInputModule, UnLuaEnhancedInput);
