// Copyright 2022 CQUnreal. All Rights Reserved.

#include "GameFramework/UnLuaCharacter.h"
#include "GameFramework/UnLuaCharacterMovementComponent.h"
#include "GameFramework/DamageType.h"
#if ENGINE_MAJOR_VERSION >= 5
#include "Engine/DamageEvents.h"
#endif


AUnLuaCharacter::AUnLuaCharacter(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UUnLuaCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{

}

void AUnLuaCharacter::PreInitializeComponents()
{
	Super::PreInitializeComponents();

	ReceivePreInitializeComponents();
}

void AUnLuaCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	ReceivePostInitializeComponents();
}

void AUnLuaCharacter::Restart()
{
	Super::Restart();

	ReceiveRestart();
}

void AUnLuaCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	PlayerStateChanged();
}

float AUnLuaCharacter::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	UDamageType const* const DamageTypeCDO = DamageEvent.DamageTypeClass ? DamageEvent.DamageTypeClass->GetDefaultObject<UDamageType>() : GetDefault<UDamageType>();
	const float ModifyDamage = ReceiveModifyDamage(Damage, DamageTypeCDO, EventInstigator, DamageCauser);

	return Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
}

bool AUnLuaCharacter::TeleportTo(const FVector& DestLocation, const FRotator& DestRotation, bool bIsATest, bool bNoCheck)
{
	bool bResult = Super::TeleportTo(DestLocation, DestRotation, bIsATest, bNoCheck);

	ReceiveTeleportTo(DestLocation, DestRotation, bResult);

	return bResult;
}

void AUnLuaCharacter::MoveBlockedBy(const FHitResult & Impact)
{
	Super::MoveBlockedBy(Impact);
	ReceiveMoveBlockedBy(Impact);
}

float AUnLuaCharacter::ReceiveModifyDamage_Implementation(float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	return Damage;
}

void AUnLuaCharacter::MulticastPlayAnimMontage_Implementation(class UAnimMontage* AnimMontage, float InPlayRate, FName StartSectionName, bool bSkipOwner)
{
	if (bSkipOwner && GetLocalRole() == ROLE_AutonomousProxy)
	{
		return;
	}

	PlayAnimMontage(AnimMontage, InPlayRate, StartSectionName);
}

void AUnLuaCharacter::MulticastStopAnimMontage_Implementation(class UAnimMontage* AnimMontage, bool bSkipOwner)
{
	if (bSkipOwner && GetLocalRole() == ROLE_AutonomousProxy)
	{
		return;
	}

	StopAnimMontage(AnimMontage);
}