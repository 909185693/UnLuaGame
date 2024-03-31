// Copyright 2022 CQUnreal. All Rights Reserved.

#include "HttpRequest.h"
#include "Misc/EngineVersionComparison.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(HttpRequest)


UHttpRequest::UHttpRequest()
	: Super()
{
	if (!HasAnyFlags(RF_ClassDefaultObject))
	{
		HttpRequest = FHttpModule::Get().CreateRequest();
		HttpRequest->OnProcessRequestComplete().BindUObject(this, &ThisClass::ProcessRequestComplete);

	#if UE_VERSION_OLDER_THAN(5, 3, 0)
		HttpRequest->OnRequestProgress().BindUObject(this, &ThisClass::RequestProgress);
	#else
		HttpRequest->OnRequestProgress64().BindUObject(this, &ThisClass::RequestProgress);
	#endif

	#if UE_VERSION_NEWER_THAN(4, 25, 0)
		HttpRequest->OnRequestWillRetry().BindUObject(this, &ThisClass::RequestWillRetry);
	#endif

	#if UE_VERSION_NEWER_THAN(4, 20, 0)
		HttpRequest->OnHeaderReceived().BindUObject(this, &ThisClass::HeaderReceived);
	#endif
	}
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
	if (HttpRequest.IsValid())
	{
		HttpRequest->CancelRequest();
	}

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
	if (HttpRequest.IsValid())
	{
		HttpRequest->SetVerb(Verb);
	}
}

void UHttpRequest::SetURL(const FString& URL)
{
	if (HttpRequest.IsValid())
	{
		HttpRequest->SetURL(URL);
	}
}

void UHttpRequest::SetContent(const TArray<uint8>& ContentPayload)
{
	if (HttpRequest.IsValid())
	{
		HttpRequest->SetContent(ContentPayload);
	}
}

void UHttpRequest::SetContentAsString(const FString& ContentString)
{
	if (HttpRequest.IsValid())
	{
		HttpRequest->SetContentAsString(ContentString);
	}
}

bool UHttpRequest::SetContentAsStreamedFile(const FString& Filename)
{
	if (HttpRequest.IsValid())
	{
		return HttpRequest->SetContentAsStreamedFile(Filename);
	}

	return false;
}

void UHttpRequest::SetHeader(const FString& HeaderName, const FString& HeaderValue)
{
	if (HttpRequest.IsValid())
	{
		HttpRequest->SetHeader(HeaderName, HeaderValue);
	}
}

void UHttpRequest::SetTimeout(float InTimeoutSecs)
{
#if ENGINE_MAJOR_VERSION > 4 || (ENGINE_MAJOR_VERSION == 4 && ENGINE_MINOR_VERSION > 24)
	if (HttpRequest.IsValid())
	{
		HttpRequest->SetTimeout(InTimeoutSecs);
	}
#endif
}

void UHttpRequest::ClearTimeout()
{
#if ENGINE_MAJOR_VERSION > 4 || (ENGINE_MAJOR_VERSION == 4 && ENGINE_MINOR_VERSION > 24)
	if (HttpRequest.IsValid())
	{
		HttpRequest->ClearTimeout();
	}
#endif
}

bool UHttpRequest::ProcessRequest()
{
	if (HttpRequest.IsValid())
	{
		return HttpRequest->ProcessRequest();
	}

	return false;
}

void UHttpRequest::CancelRequest()
{
	Destroy();
}

float UHttpRequest::GetElapsedTime()
{
	if (HttpRequest.IsValid())
	{
		return HttpRequest->GetElapsedTime();
	}

	return 0.f;
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

#if UE_VERSION_OLDER_THAN(5, 3, 0)
void UHttpRequest::RequestProgress(FHttpRequestPtr Request, int32 BytesSent, int32 BytesReceived)
#else
void UHttpRequest::RequestProgress(FHttpRequestPtr Request, uint64 BytesSent, uint64 BytesReceived)
#endif
{
	OnRequestProgress.Broadcast(BytesSent, BytesReceived);
}

void UHttpRequest::RequestWillRetry(FHttpRequestPtr Request, FHttpResponsePtr Response, float SecondsToRetry)
{
	OnRequestWill.Broadcast(SecondsToRetry);
}