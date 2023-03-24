// Copyright 2022 CQUnreal. All Rights Reserved.

#include "Engine/UnLuaGameInstance.h"
#include "GameFramework/GameModeBase.h"
#include "GameFramework/PlayerState.h"
#include "GameFramework/PlayerController.h"


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
	ReceivePreLogin(GameMode, NewPlayer, NewPlayer.IsValid() ? UTF8_TO_TCHAR(NewPlayer->GetBytes()) : TEXT(""));
}

void UUnLuaGameInstance::PostLogin(AGameModeBase* GameMode, APlayerController* NewPlayer)
{
	FString PlayerUID = TEXT("");

	APlayerState* PlayerState = NewPlayer ? NewPlayer->GetPlayerState<APlayerState>() : nullptr;
#if ENGINE_MAJOR_VERSION > 4 || ENGINE_MINOR_VERSION > 24
	if (PlayerState && PlayerState->GetUniqueId().IsValid())
	{
		PlayerUID = UTF8_TO_TCHAR(PlayerState->GetUniqueId()->GetBytes());
	}
#else
	if (PlayerState && PlayerState->UniqueId.IsValid())
	{
		PlayerUID = UTF8_TO_TCHAR(PlayerState->UniqueId->GetBytes());
	}
#endif

	ReceivePostLogin(GameMode, NewPlayer, PlayerUID);
}

void UUnLuaGameInstance::Logout(AGameModeBase* GameMode, AController* Exiting)
{
	FString PlayerUID = TEXT("");

	APlayerState* PlayerState = Exiting ? Exiting->GetPlayerState<APlayerState>() : nullptr;
#if ENGINE_MAJOR_VERSION > 4 || ENGINE_MINOR_VERSION > 24
	if (PlayerState && PlayerState->GetUniqueId().IsValid())
	{
		PlayerUID = UTF8_TO_TCHAR(PlayerState->GetUniqueId()->GetBytes());
	}
#else
	if (PlayerState && PlayerState->UniqueId.IsValid())
	{
		PlayerUID = UTF8_TO_TCHAR(PlayerState->UniqueId->GetBytes());
	}
#endif
	
	ReceiveLogout(GameMode, Exiting, PlayerUID);
}

void UUnLuaGameInstance::ForceGC()
{
	GEngine->ForceGarbageCollection(true);
}

bool UUnLuaGameInstance::IsDedicatedServer() const
{
	return Super::IsDedicatedServerInstance();
}