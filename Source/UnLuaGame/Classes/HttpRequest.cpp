// Copyright 2022 CQUnreal. All Rights Reserved.

#include "HttpRequest.h"


UHttpRequest::UHttpRequest()
	: Super()
{
	HttpRequest->OnProcessRequestComplete().BindUObject(this, &UHttpRequest::ProcessRequestComplete);
	HttpRequest->OnRequestProgress().BindUObject(this, &UHttpRequest::RequestProgress);
#if ENGINE_MAJOR_VERSION > 4 || (ENGINE_MAJOR_VERSION == 4 && ENGINE_MINOR_VERSION >= 25)
	HttpRequest->OnRequestWillRetry().BindUObject(this, &UHttpRequest::RequestWillRetry);
#endif
#if ENGINE_MAJOR_VERSION > 4 || (ENGINE_MAJOR_VERSION == 4 && ENGINE_MINOR_VERSION >= 20)
	HttpRequest->OnHeaderReceived().BindUObject(this, &UHttpRequest::HeaderReceived);
#endif
}

void UHttpRequest::Destroy()
{
	if (!HasAnyFlags(RF_BeginDestroyed))
	{
		RemoveFromRoot();

		ConditionalBeginDestroy();
	}
}

void UHttpRequest::BeginDestroy()
{
	HttpRequest->CancelRequest();

	Super::BeginDestroy();
}

UHttpRequest* UHttpRequest::Create()
{
	UHttpRequest* NewHttpRequest = NewObject<UHttpRequest>();
	NewHttpRequest->AddToRoot();
	return NewHttpRequest;
	//return new UHttpRequest();
}

void UHttpRequest::SetVerb(const FString& Verb)
{
	HttpRequest->SetVerb(Verb);
}

void UHttpRequest::SetURL(const FString& URL)
{
	HttpRequest->SetURL(URL);
}

void UHttpRequest::SetContent(const TArray<uint8>& ContentPayload)
{
	HttpRequest->SetContent(ContentPayload);
}

void UHttpRequest::SetContentAsString(const FString& ContentString)
{
	HttpRequest->SetContentAsString(ContentString);
}

bool UHttpRequest::SetContentAsStreamedFile(const FString& Filename)
{
	return HttpRequest->SetContentAsStreamedFile(Filename);
}

void UHttpRequest::SetHeader(const FString& HeaderName, const FString& HeaderValue)
{
	HttpRequest->SetHeader(HeaderName, HeaderValue);
}

void UHttpRequest::SetTimeout(float InTimeoutSecs)
{
#if ENGINE_MAJOR_VERSION > 4 || (ENGINE_MAJOR_VERSION == 4 && ENGINE_MINOR_VERSION > 24)
	HttpRequest->SetTimeout(InTimeoutSecs);
#endif
}

void UHttpRequest::ClearTimeout()
{
#if ENGINE_MAJOR_VERSION > 4 || (ENGINE_MAJOR_VERSION == 4 && ENGINE_MINOR_VERSION > 24)
	HttpRequest->ClearTimeout();
#endif
}

bool UHttpRequest::ProcessRequest()
{
	return HttpRequest->ProcessRequest();
}

void UHttpRequest::CancelRequest()
{
	Destroy();
}

float UHttpRequest::GetElapsedTime()
{
	return HttpRequest->GetElapsedTime();
}

void UHttpRequest::ProcessRequestComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
{
	if (Response.IsValid())
	{
		OnProcessRequestComplete.Broadcast(bConnectedSuccessfully, Response->GetResponseCode(), Response->GetContentAsString());
	}
	else
	{
		OnProcessRequestComplete.Broadcast(false, 0, TEXT(""));
	}

	OnProcessRequestComplete.Clear();

	Destroy();
}

void UHttpRequest::HeaderReceived(FHttpRequestPtr Request, const FString& HeaderName, const FString& NewHeaderValue)
{
	OnHeaderReceived.Broadcast(HeaderName, NewHeaderValue);
}

void UHttpRequest::RequestProgress(FHttpRequestPtr Request, int32 BytesSent, int32 BytesReceived)
{
	OnRequestProgress.Broadcast(BytesSent, BytesReceived);
}

void UHttpRequest::RequestWillRetry(FHttpRequestPtr Request, FHttpResponsePtr Response, float SecondsToRetry)
{
	OnRequestWill.Broadcast(SecondsToRetry);
}