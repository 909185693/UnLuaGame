// Copyright 2022 CQUnreal. All Rights Reserved.

#include "UnLuaGameplayAbilitiesPrivate.h"
#include "Modules/ModuleManager.h"

class FUnLuaGameplayAbilitiesModule : public IModuleInterface
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

IMPLEMENT_MODULE(FUnLuaGameplayAbilitiesModule, UnLuaGameplayAbilities);
