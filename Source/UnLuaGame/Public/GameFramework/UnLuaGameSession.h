// Copyright 2022 CQUnreal. All Rights Reserved.

#pragma once

#include "Online.h"
#include "CoreMinimal.h"
#include "GameFramework/GameSession.h"
#include "UnLuaGameSession.generated.h"

/**
 * GameSession
 */
UCLASS(BlueprintType, Blueprintable)
class UNLUAGAME_API AUnLuaGameSession : public AGameSession
{
	GENERATED_UCLASS_BODY()

	/** Allow a dedicated server a chance to register itself with an online service */
	virtual void RegisterServer() override;	

	/*
	 * Event triggered when a presence session is created
	 *
	 * @param SessionName name of session that was created
	 * @param bWasSuccessful was the create successful
	 */
	DECLARE_EVENT_TwoParams(AUnLuaGameSession, FOnCreatePresenceSessionComplete, FName /*SessionName*/, bool /*bWasSuccessful*/);
	FOnCreatePresenceSessionComplete CreatePresenceSessionCompleteEvent;

public:
	/** @return the delegate fired when creating a presence session */
	FOnCreatePresenceSessionComplete& OnCreatePresenceSessionComplete() { return CreatePresenceSessionCompleteEvent; }

	/** Handles to various registered delegates */
	FDelegateHandle OnCreateSessionCompleteDelegateHandle;

protected:
	/** Delegate for creating a new session */
	FOnCreateSessionCompleteDelegate OnCreateSessionCompleteDelegate;

	/**
	 * Delegate fired when a session create request has completed
	 *
	 * @param SessionName the name of the session this callback is for
	 * @param bWasSuccessful true if the async action completed without error, false if there was an error
	 */
	virtual void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);
};
