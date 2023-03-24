// Copyright 2022 CQUnreal. All Rights Reserved.

#include "UnLuaEx.h"
#include "LuaCore.h"
#include "LuaDynamicBinding.h"
#include "Kismet/GameplayStatics.h"


static TArray<APlayerController*> UGameplayStatics_GetPlayerControllerArray(UObject* WorldContextObject)
{
	TArray<APlayerController*> Results;
	if (UWorld* World = WorldContextObject ? WorldContextObject->GetWorld() : nullptr)
	{
		for (FConstPlayerControllerIterator Iterator = World->GetPlayerControllerIterator(); Iterator; ++Iterator)
		{
			APlayerController* PlayerController = Iterator->Get();
			if (PlayerController != nullptr)
			{
				Results.Add(PlayerController);
			}
		}
	}
	else
	{
		UE_LOG(LogUnLua, Log, TEXT("%s: Invalid WorldContextObject!"), ANSI_TO_TCHAR(__FUNCTION__));
	}

	return Results;
}

static TArray<APawn*> UGameplayStatics_GetPlayerPawnArray(UObject* WorldContextObject)
{
	TArray<APawn*> Results;
	if (UWorld* World = WorldContextObject ? WorldContextObject->GetWorld() : nullptr)
	{
		for (FConstPlayerControllerIterator Iterator = World->GetPlayerControllerIterator(); Iterator; ++Iterator)
		{
			APlayerController* PlayerController = Iterator->Get();
			APawn* Pawn = PlayerController ? PlayerController->GetPawn() : nullptr;
			if (Pawn != nullptr)
			{
				Results.Add(Pawn);
			}
		}
	}
	else
	{
		UE_LOG(LogUnLua, Log, TEXT("%s: Invalid WorldContextObject!"), ANSI_TO_TCHAR(__FUNCTION__));
	}

	return Results;
}

static const luaL_Reg UGameplayStaticsLib[] =
{
    { nullptr, nullptr }
};

BEGIN_EXPORT_REFLECTED_CLASS(UGameplayStatics)
	ADD_EXTERNAL_FUNCTION_EX("GetPlayerControllerArray", TArray<APlayerController*>, UGameplayStatics_GetPlayerControllerArray)
	ADD_EXTERNAL_FUNCTION_EX("GetPlayerPawnArray", TArray<APawn*>, UGameplayStatics_GetPlayerPawnArray)
    ADD_LIB(UGameplayStaticsLib)
END_EXPORT_CLASS()
IMPLEMENT_EXPORTED_CLASS(UGameplayStatics)
