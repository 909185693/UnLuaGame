// Copyright 2022 CQUnreal. All Rights Reserved.

#include "GameFramework/UnLuaActor.h"

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