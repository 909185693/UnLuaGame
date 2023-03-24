// Copyright 2022 CQUnreal. All Rights Reserved.

#include "GameFramework/UnLuaHUD.h"
#include "Engine/Texture.h"
#include "Engine/LocalPlayer.h"
#include "Engine/UserInterfaceSettings.h"


const float AUnLuaHUD::MinHudScale = 0.5f;

AUnLuaHUD::AUnLuaHUD(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void AUnLuaHUD::DrawHUD()
{
	Super::DrawHUD();

	if (!IsCanvasValid_WarnIfNot())
	{
		return;
	}

	const UUserInterfaceSettings* UserInterfaceSettings = GetDefault<UUserInterfaceSettings>();
	if (UserInterfaceSettings != nullptr)
	{
		ScaleUI = Canvas->ClipY / UserInterfaceSettings->DesignScreenSize.Y;
	}
	else
	{
		ScaleUI = Canvas->ClipY / 1080.0f;
	}

	// make any adjustments for splitscreen
	int32 SSPlayerIndex = 0;
	if (PlayerOwner && PlayerOwner->IsSplitscreenPlayer(&SSPlayerIndex))
	{
		ULocalPlayer* const LP = Cast<ULocalPlayer>(PlayerOwner->Player);
		if (LP)
		{
			const ESplitScreenType::Type SSType = LP->ViewportClient->GetCurrentSplitscreenConfiguration();

			if ((SSType == ESplitScreenType::TwoPlayer_Horizontal) ||
				(SSType == ESplitScreenType::ThreePlayer_FavorBottom && SSPlayerIndex == 2) ||
				(SSType == ESplitScreenType::ThreePlayer_FavorTop && SSPlayerIndex == 0))
			{
				// full-width splitscreen viewports can handle same size HUD elements as full-screen viewports
				ScaleUI *= 2.f;
			}
		}
	}

	// enforce min
	ScaleUI = FMath::Max(ScaleUI, MinHudScale);
}

FCanvasIcon AUnLuaHUD::MakeIcon(UTexture* Texture, float U, float V, float UL, float VL)
{
	FCanvasIcon NewIcon;
	NewIcon.Texture = Texture;
	NewIcon.U = U;
	NewIcon.V = V;
	NewIcon.UL = UL;
	NewIcon.VL = VL;
	return NewIcon;
}

void AUnLuaHUD::SetDrawColor(uint8 R, uint8 G, uint8 B, uint8 A)
{
	if (IsCanvasValid_WarnIfNot())
	{
		Canvas->SetDrawColor(R, G, B, A);
	}
}

void AUnLuaHUD::DrawScaledIcon(FCanvasIcon Icon, float X, float Y, FVector Scale)
{
	if (IsCanvasValid_WarnIfNot())
	{
		Canvas->DrawScaledIcon(Icon, X, Y, Scale);
	}
}

void AUnLuaHUD::DrawIcon(FCanvasIcon Icon, float X, float Y, float Scale)
{
	if (IsCanvasValid_WarnIfNot())
	{
		Canvas->DrawIcon(Icon, X, Y, Scale);
	}
}