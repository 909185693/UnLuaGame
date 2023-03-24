// Copyright 2022 CQUnreal. All Rights Reserved.

#include "GameFramework/UnLuaGameMode.h"
#include "Net/OnlineEngineInterface.h"
#include "GameFramework/GameSession.h"


AUnLuaGameMode::AUnLuaGameMode(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void AUnLuaGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	ReceiveInitGame(MapName, Options);
}

void AUnLuaGameMode::InitGameState()
{
	Super::InitGameState();

	ReceiveInitGameState();
}

void AUnLuaGameMode::PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
	ReceivePreLogin(Options, Address, UniqueId, ErrorMessage);

	if (ErrorMessage.IsEmpty())
	{
		// Login unique id must match server expected unique id type OR No unique id could mean game doesn't use them
		const bool bUniqueIdCheckOk = (!UniqueId.IsValid() || UOnlineEngineInterface::Get()->IsCompatibleUniqueNetId(*UniqueId));
		if (bUniqueIdCheckOk)
		{
			ErrorMessage = GameSession->ApproveLogin(Options);
		}
		else
		{
			ErrorMessage = TEXT("incompatible_unique_net_id");
		}
	}

	FGameModeEvents::GameModePreLoginEvent.Broadcast(this, UniqueId, ErrorMessage);
}

FString AUnLuaGameMode::InitNewPlayer(APlayerController* NewPlayerController, const FUniqueNetIdRepl& UniqueId, const FString& Options, const FString& Portal)
{
	const FString ErrorMessage = Super::InitNewPlayer(NewPlayerController, UniqueId, Options, Portal);

	ReceiveInitNewPlayer(NewPlayerController, UniqueId, Options, Portal);

	return ErrorMessage;
}

void AUnLuaGameMode::RestartPlayer(AController* NewPlayer)
{
	Super::RestartPlayer(NewPlayer);

	ReceiveRestartPlayer(NewPlayer);
}

void AUnLuaGameMode::RestartPlayerAtPlayerStart(AController* NewPlayer, AActor* StartSpot)
{
	Super::RestartPlayerAtPlayerStart(NewPlayer, StartSpot);

	ReceiveRestartPlayerAtPlayerStart(NewPlayer, StartSpot);
}

void AUnLuaGameMode::RestartPlayerAtTransform(AController* NewPlayer, const FTransform& SpawnTransform)
{
	Super::RestartPlayerAtTransform(NewPlayer, SpawnTransform);

	ReceiveRestartPlayerAtTransform(NewPlayer, SpawnTransform);
}