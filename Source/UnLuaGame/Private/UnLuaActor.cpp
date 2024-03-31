// Copyright 2022 CQUnreal. All Rights Reserved.

#include "GameFramework/UnLuaActor.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(UnLuaActor)


AUnLuaActor::AUnLuaActor(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void AUnLuaActor::PreInitializeComponents()
{
	Super::PreInitializeComponents();

	ReceivePreInitializeComponents();
}

void AUnLuaActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	ReceivePostInitializeComponents();
}