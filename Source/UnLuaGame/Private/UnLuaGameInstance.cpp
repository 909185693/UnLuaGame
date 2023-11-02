// Copyright 2022 CQUnreal. All Rights Reserved.

#include "Engine/UnLuaGameInstance.h"
#include "GameFramework/GameModeBase.h"
#include "GameFramework/PlayerState.h"
#include "GameFramework/PlayerController.h"

static int32 ControllerCount = 0;

UUnLuaGameInstance::UUnLuaGameInstance(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

ULocalPlayer* UUnLuaGameInstance::CreateInitialPlayer(FString& OutError)
{
	return CreateLocalPlayer(ControllerCount++, OutError, false);
}

bool UUnLuaGameInstance::RemoveLocalPlayer(ULocalPlayer* ExistingPlayer)
{
	ControllerCount--;

	return Super::RemoveLocalPlayer(ExistingPlayer);
}

void UUnLuaGameInstance::Init()
{
	PreLoadMapHandle = FCoreUObjectDelegates::PreLoadMap.AddUObject(this, &UUnLuaGameInstance::PreLoadMap);
	PostLoadMapWithWorldHandle = FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &UUnLuaGameInstance::PostLoadMapWithWorld);
	PreLoginHandle = FGameModeEvents::GameModePreLoginEvent.AddUObject(this, &UUnLuaGameInstance::PreLogin);
	PostLoginHandle = FGameModeEvents::GameModePostLoginEvent.AddUObject(this, &UUnLuaGameInstance::PostLogin);
	LogoutHandle = FGameModeEvents::GameModeLogoutEvent.AddUObject(this, &UUnLuaGameInstance::Logout);

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