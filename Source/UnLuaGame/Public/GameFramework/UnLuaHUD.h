// Copyright 2022 CQUnreal. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/Canvas.h"
#include "GameFramework/HUD.h"
#include "UnLuaHUD.generated.h"


UCLASS()
class UNLUAGAME_API AUnLuaHUD : public AHUD
{
	GENERATED_UCLASS_BODY()

public:
	/** Main HUD update loop. */
	virtual void DrawHUD() override;

	/** Holds texture information with UV coordinates as well. */
	UFUNCTION(BlueprintCallable, Category = HUD)
	FCanvasIcon MakeIcon(class UTexture* Texture, float U, float V, float UL, float VL);

	/** Set draw color. (FColor) */
	UFUNCTION(BlueprintCallable, Category = HUD)
	void SetDrawColor(uint8 R, uint8 G, uint8 B, uint8 A = 255);

	/** Draw a scaled CanvasIcon at the desired canvas position. */
	UFUNCTION(BlueprintCallable, Category = HUD, meta = (AdvancedDisplay = "9"))
	void DrawScaledIcon(FCanvasIcon Icon, float X, float Y, FVector Scale);

	/** Draw a CanvasIcon at the desired canvas position.	 */
	UFUNCTION(BlueprintCallable, Category = HUD, meta = (AdvancedDisplay = "9"))
	void DrawIcon(FCanvasIcon Icon, float X, float Y, float Scale = 0.f);

protected:
	/** Floor for automatic hud scaling. */
	static const float MinHudScale;

	/** UI scaling factor for other resolutions than Full HD. */
	UPROPERTY(BlueprintReadOnly, Category = HUD)
	float ScaleUI;
};
