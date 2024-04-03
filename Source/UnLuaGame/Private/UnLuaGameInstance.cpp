// Copyright 2022 CQUnreal. All Rights Reserved.

#include "Engine/UnLuaGameInstance.h"
#include "GameFramework/GameModeBase.h"
#include "GameFramework/PlayerState.h"
#include "GameFramework/PlayerController.h"
#include "UnLuaGamePrivate.h"
#if UE_EDITOR
#include "UnLua.h"
#endif

#include UE_INLINE_GENERATED_CPP_BY_NAME(UnLuaGameInstance)


UUnLuaGameInstance::UUnLuaGameInstance(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void UUnLuaGameInstance::Init()
{
	PreLoadMapHandle = FCoreUObjectDelegates::PreLoadMap.AddUObject(this, &UUnLuaGameInstance::PreLoadMap);
	PostLoadMapWithWorldHandle = FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &UUnLuaGameInstance::PostLoadMapWithWorld);
	PreLoginHandle = FGameModeEvents::GameModePreLoginEvent.AddUObject(this, &UUnLuaGameInstance::PreLogin);
	PostLoginHandle = FGameModeEvents::GameModePostLoginEvent.AddUObject(this, &UUnLuaGameInstance::PostLogin);
	LogoutHandle = FGameModeEvents::GameModeLogoutEvent.AddUObject(this, &UUnLuaGameInstance::Logout);

	StartLuaDebuger();

	Super::Init();
}

void UUnLuaGameInstance::Shutdown()
{
	FCoreUObjectDelegates::PreLoadMap.Remove(PreLoadMapHandle);
	FCoreUObjectDelegates::PostLoadMapWithWorld.Remove(PostLoadMapWithWorldHandle);
	FGameModeEvents::GameModePreLoginEvent.Remove(PreLoginHandle);
	FGameModeEvents::GameModePostLoginEvent.Remove(PostLoginHandle);
	FGameModeEvents::GameModeLogoutEvent.Remove(LogoutHandle);

	Super::Shutdown();
}

void UUnLuaGameInstance::OnStart()
{
	Super::OnStart();

	ReceiveOnStart();
}

void UUnLuaGameInstance::PreLoadMap(const FString& MapName)
{
	ReceivePreLoadMap(MapName);
}

void UUnLuaGameInstance::PostLoadMapWithWorld(UWorld* LoadedWorld)
{
	ReceivePostLoadMapWithWorld(LoadedWorld);
}

void UUnLuaGameInstance::PreLogin(AGameModeBase* GameMode, const FUniqueNetIdRepl& NewPlayer, FString& ErrorMessage)
{
	ReceivePreLogin(GameMode, NewPlayer);
}

void UUnLuaGameInstance::PostLogin(AGameModeBase* GameMode, APlayerController* NewPlayer)
{
	ReceivePostLogin(GameMode, NewPlayer);
}
 
void UUnLuaGameInstance::Logout(AGameModeBase* GameMode, AController* Exiting)
{
	ReceiveLogout(GameMode, Exiting);
}

void UUnLuaGameInstance::ForceGC()
{
	GEngine->ForceGarbageCollection(true);
}

bool UUnLuaGameInstance::IsDedicatedServer() const
{
	return Super::IsDedicatedServerInstance();
}

void UUnLuaGameInstance::StartLuaDebuger()
{
	if (FWorldContext* InstanceWorldContext = GetWorldContext())
	{
		for (const FLuaDebug& LuaDeug : LuaDebugs)
		{
			if (LuaDeug.PIEInstance == InstanceWorldContext->PIEInstance)
			{
				for (TPair<lua_State*, UnLua::FLuaEnv*> Pair : UnLua::FLuaEnv::GetAll())
				{
					if (Pair.Key && Pair.Value)
					{
						UE_LOG(LogUnLuaGame, Log, TEXT("Connect lua debuger: %s:%d"), *LuaDeug.IP, LuaDeug.Port);

						Pair.Value->DoString(FString::Printf(TEXT("require(\"LuaPanda\").start(\"%s\", %d)"), *LuaDeug.IP, LuaDeug.Port));
					}
				}
			}
		}
	}
}