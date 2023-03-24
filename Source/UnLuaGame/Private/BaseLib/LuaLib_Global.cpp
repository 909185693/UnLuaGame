// Copyright 2022 CQUnreal. All Rights Reserved.

#include "UnLuaEx.h"
#include "LuaCore.h"
#include "LuaDynamicBinding.h"
#include "Online.h"
#include "SocketSubsystem.h"
#include "Engine/World.h"
#include "GameFramework/OnlineReplStructs.h"

#define BigLittleSwap32(A)  ((((uint32)(A) & 0xff000000) >> 24) | (((uint32)(A) & 0x00ff0000) >> 8) | (((uint32)(A) & 0x0000ff00) << 8) | (((uint32)(A) & 0x000000ff) << 24))

static TArray<uint8> Global_MakeByteArray(const char* Data, int32 Size)
{
	return TArray<uint8>((uint8*)Data, Size);
}

static const char* Global_ByteArrayToChar(const TArray<uint8>& DataArray)
{
	return (const char*)DataArray.GetData();
}

static bool Global_PraseIP(const FString& Domain, FString& OutIP)
{
	ISocketSubsystem* SocketSubsystem = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM);
	if (SocketSubsystem != nullptr)
	{
		FString HostName;
		FString ServiceName;
		if (Domain.Split("://", &ServiceName, &HostName))
		{
			FAddressInfoResult AddressInfoResult = SocketSubsystem->GetAddressInfo(*HostName, *ServiceName, EAddressInfoFlags::AllResults, FNetworkProtocolTypes::IPv4, SOCKTYPE_Unknown);
			if (AddressInfoResult.ReturnCode == ESocketErrors::SE_NO_ERROR && AddressInfoResult.Results.Num() > 0)
			{
				OutIP = AddressInfoResult.Results[0].Address->ToString(false);

				return true;
			}
		}
		else
		{
			FAddressInfoResult AddressInfoResult = SocketSubsystem->GetAddressInfo(*Domain, TEXT(""), EAddressInfoFlags::AllResults, FNetworkProtocolTypes::IPv4, SOCKTYPE_Unknown);
			if (AddressInfoResult.ReturnCode == ESocketErrors::SE_NO_ERROR && AddressInfoResult.Results.Num() > 0)
			{
				OutIP = AddressInfoResult.Results[0].Address->ToString(false);

				return true;
			}
		}
	}

	return false;
}

static FString Global_ConvertIPIntToString(int32 IP)
{
	TSharedRef<class FInternetAddr> NewInternetAddr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	NewInternetAddr->SetIp(BigLittleSwap32(IP));

	return NewInternetAddr->ToString(false);
}

static FString Global_ConvertUniqueNetId(const FUniqueNetIdRepl& UniqueNetId)
{
	if (!UniqueNetId.IsValid())
	{
		return TEXT("");
	}

	return UTF8_TO_TCHAR((const char*)UniqueNetId->GetBytes());
}

static int32 Global_ConvertIPStringToInt(FString IP)
{
	TSharedRef<class FInternetAddr> NewInternetAddr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	bool bIsValid = false;
	NewInternetAddr->SetIp(*IP, bIsValid);

	uint32 OutAddr = 0;
	NewInternetAddr->GetIp(OutAddr);

	return OutAddr;
}

static int32 Global_GetPlayInEditorID()
{
#if UE_EDITOR
	return FMath::Max(0, GPlayInEditorID);
#else
	return 0;
#endif
}

static bool Global_IsPlayInEditor(UObject* WorldContentObject)
{
	UWorld* World = WorldContentObject ? WorldContentObject->GetWorld() : nullptr;
	return World ? World->IsPlayInEditor() : false;
}

static bool Global_IsLocalPlayerTalking(int32 LocalUserNum)
{
	IOnlineVoicePtr VoiceInt = Online::GetVoiceInterface();
	if (!VoiceInt.IsValid())
	{
		UE_LOG(LogUnLua, Log, TEXT("%s: Invalid VoiceInterface!"), ANSI_TO_TCHAR(__FUNCTION__));
		return false;
	}

	return VoiceInt->IsLocalPlayerTalking(LocalUserNum);
}

static bool Global_IsRemotePlayerTalking(const FUniqueNetIdRepl& PlayerNetId)
{
	if (!PlayerNetId.IsValid())
	{
		// UE_LOG(LogUnLua, Log, TEXT("%s: Invalid PlayerNetId!"), ANSI_TO_TCHAR(__FUNCTION__));
		return false;
	}

	IOnlineVoicePtr VoiceInt = Online::GetVoiceInterface();
	if (!VoiceInt.IsValid())
	{
		UE_LOG(LogUnLua, Log, TEXT("%s: Invalid VoiceInterface!"), ANSI_TO_TCHAR(__FUNCTION__));
		return false;
	}

	return VoiceInt->IsRemotePlayerTalking(*PlayerNetId);
}

EXPORT_FUNCTION_EX(MakeByteArray, TArray<uint8>, Global_MakeByteArray, const char*, int32)
EXPORT_FUNCTION_EX(ByteArrayToChar, const char*, Global_ByteArrayToChar, const TArray<uint8>&)
EXPORT_FUNCTION_EX(PraseIP, bool, Global_PraseIP, const FString&, FString&)
EXPORT_FUNCTION_EX(ConvertIPIntToString, FString, Global_ConvertIPIntToString, int32)
EXPORT_FUNCTION_EX(ConvertUniqueNetId, FString, Global_ConvertUniqueNetId, const FUniqueNetIdRepl&)
EXPORT_FUNCTION_EX(ConvertIPStringToInt, int32, Global_ConvertIPStringToInt, FString)
EXPORT_FUNCTION_EX(GetPlayInEditorID, int32, Global_GetPlayInEditorID)
EXPORT_FUNCTION_EX(IsPlayInEditor, bool, Global_IsPlayInEditor, UObject*)
EXPORT_FUNCTION_EX(IsLocalPlayerTalking, bool, Global_IsLocalPlayerTalking, int32)
EXPORT_FUNCTION_EX(IsRemotePlayerTalking, bool, Global_IsRemotePlayerTalking, const FUniqueNetIdRepl&)

