// Copyright 2022 CQUnreal. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "UnLuaGameMode.generated.h"


UCLASS()
class UNLUAGAME_API AUnLuaGameMode : public AGameMode
{
	GENERATED_UCLASS_BODY()

	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	virtual void InitGameState() override;
	virtual void PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage) override;
	virtual FString InitNewPlayer(APlayerController* NewPlayerController, const FUniqueNetIdRepl& UniqueId, const FString& Options, const FString& Portal = TEXT("")) override;
	virtual void RestartPlayer(AController* NewPlayer) override;
	virtual void RestartPlayerAtPlayerStart(AController* NewPlayer, AActor* StartSpot) override;
	virtual void RestartPlayerAtTransform(AController* NewPlayer, const FTransform& SpawnTransform) override;

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = Game, Meta = (DisplayName = "PreLogin"))
	void ReceivePreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage);

	UFUNCTION(BlueprintImplementableEvent, Category = Game, Meta = (DisplayName="InitGame"))
	void ReceiveInitGame(const FString& MapName, const FString& Options);

	UFUNCTION(BlueprintImplementableEvent, Category = Game, Meta = (DisplayName = "InitGameState"))
	void ReceiveInitGameState();

	UFUNCTION(BlueprintImplementableEvent, Category = Game, Meta = (DisplayName = "InitNewPlayer"))
	void ReceiveInitNewPlayer(APlayerController* NewPlayerController, const FUniqueNetIdRepl& UniqueId, const FString& Options, const FString& Portal);

	UFUNCTION(BlueprintImplementableEvent, Category = Game, Meta = (DisplayName = "RestartPlayer"))
	void ReceiveRestartPlayer(AController* NewPlayer);

	UFUNCTION(BlueprintImplementableEvent, Category = Game, Meta = (DisplayName = "RestartPlayerAtPlayerStart"))
	void ReceiveRestartPlayerAtPlayerStart(AController* NewPlayer, AActor* StartSpot);

	UFUNCTION(BlueprintImplementableEvent, Category = Game, Meta = (DisplayName = "RestartPlayerAtTransform"))
	void ReceiveRestartPlayerAtTransform(AController* NewPlayer, const FTransform& SpawnTransform);
};
