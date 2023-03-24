// Copyright 2022 CQUnreal. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "UnLuaCharacter.generated.h"


UCLASS()
class UNLUAGAME_API AUnLuaCharacter : public ACharacter
{
	GENERATED_UCLASS_BODY()

	virtual void PreInitializeComponents() override;
	virtual void PostInitializeComponents() override;

	virtual void Restart() override;
	virtual void OnRep_PlayerState() override;
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	virtual bool TeleportTo(const FVector& DestLocation, const FRotator& DestRotation, bool bIsATest = false, bool bNoCheck = false) override;
	virtual void MoveBlockedBy(const FHitResult& Impact) override;

	UFUNCTION(BlueprintImplementableEvent, meta = (BlueprintInternalUseOnly = "true", DisplayName = "PreInitializeComponents"))
	void ReceivePreInitializeComponents();

	UFUNCTION(BlueprintImplementableEvent, meta = (BlueprintInternalUseOnly = "true", DisplayName = "PostInitializeComponents"))
	void ReceivePostInitializeComponents();

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "PlayerStateChanged"), Category = "Game|Pawn")
	void PlayerStateChanged();

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "Restart"), Category = "Game|Pawn")
	void ReceiveRestart();

	UFUNCTION(BlueprintNativeEvent, meta = (DisplayName = "ModifyDamage"), Category = "Game|Damage")
	float ReceiveModifyDamage(float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "TeleportTo"), Category = "Game|Pawn")
	void ReceiveTeleportTo(FVector DestLocation, FRotator DestRotation, bool bWasSuccessful);

	UFUNCTION(NetMulticast, Reliable)
	void MulticastPlayAnimMontage(class UAnimMontage* AnimMontage, float InPlayRate = 1.f, FName StartSectionName = NAME_None, bool bSkipOwner = false);

	UFUNCTION(NetMulticast, Reliable)
	void MulticastStopAnimMontage(class UAnimMontage* AnimMontage, bool bSkipOwner = false);

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "MoveBlocked"), Category = "Move")
	void ReceiveMoveBlockedBy(const FHitResult& Impact);
};
