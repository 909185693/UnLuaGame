// Copyright 2022 CQUnreal. All Rights Reserved.

#pragma once

#include "Http.h"
#include "HttpRequest.generated.h"


/**
 * UHttpRequest
 */
UCLASS()
class UNLUAGAME_API UHttpRequest : public UObject
{
	GENERATED_BODY()

public:
	UHttpRequest();

	virtual void Destroy();
	virtual void BeginDestroy() override;

	UFUNCTION(BlueprintCallable, Category = Http)
	static UHttpRequest* Create();

	UFUNCTION(BlueprintCallable, Category = Http)
	void SetVerb(const FString& Verb);

	UFUNCTION(BlueprintCallable, Category = Http)
	void SetURL(const FString& URL);

	UFUNCTION(BlueprintCallable, Category = Http)
	void SetContent(const TArray<uint8>& ContentPayload);

	UFUNCTION(BlueprintCallable, Category = Http)
	void SetContentAsString(const FString& ContentString);

	UFUNCTION(BlueprintCallable, Category = Http)
	bool SetContentAsStreamedFile(const FString& Filename);

	UFUNCTION(BlueprintCallable, Category = Http)
	void SetHeader(const FString& HeaderName, const FString& HeaderValue);

	UFUNCTION(BlueprintCallable, Category = Http)
	void SetTimeout(float InTimeoutSecs);

	UFUNCTION(BlueprintCallable, Category = Http)
	void ClearTimeout();

	UFUNCTION(BlueprintCallable, Category = Http)
	bool ProcessRequest();

	UFUNCTION(BlueprintCallable, Category = Http)
	void CancelRequest();

	//EHttpRequestStatus::Type GetStatus();

	UFUNCTION(BlueprintCallable, Category = Http)
	float GetElapsedTime();

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FProcessRequestCompleteReply, bool, bConnectedSuccessfully, int32, ResponseCode, const FString&, ContentAsString);
	UPROPERTY(BlueprintAssignable) FProcessRequestCompleteReply OnProcessRequestComplete;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FRequestProgressReply, int32, BytesSent, int32, BytesReceived);
	UPROPERTY(BlueprintAssignable) FRequestProgressReply OnRequestProgress;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FRequestWillRetryReply, float, SecondsToRetry);
	UPROPERTY(BlueprintAssignable) FRequestWillRetryReply OnRequestWill;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FHeaderReceivedReply, const FString&, HeaderName, const FString&, NewHeaderValue);
	UPROPERTY(BlueprintAssignable) FHeaderReceivedReply OnHeaderReceived;

protected:
	void ProcessRequestComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully);
	void HeaderReceived(FHttpRequestPtr Request, const FString& HeaderName, const FString& NewHeaderValue);
	void RequestProgress(FHttpRequestPtr Request, int32 BytesSent, int32 BytesReceived);
	void RequestWillRetry(FHttpRequestPtr Request, FHttpResponsePtr Response, float SecondsToRetry);

private:
#if ENGINE_MAJOR_VERSION > 4 || (ENGINE_MAJOR_VERSION == 4 && ENGINE_MINOR_VERSION > 24)
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = FHttpModule::Get().CreateRequest();
#else
	TSharedRef<IHttpRequest, ESPMode::NotThreadSafe> HttpRequest = FHttpModule::Get().CreateRequest();
#endif
};
