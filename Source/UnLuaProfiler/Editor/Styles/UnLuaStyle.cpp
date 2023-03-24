// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "UnLuaStyle.h"
#include "Styling/SlateStyleRegistry.h"
#include "Framework/Application/SlateApplication.h"

#define IMAGE_BRUSH( RelativePath, ... ) FSlateImageBrush( Style->RootToContentDir( RelativePath, TEXT(".png") ), __VA_ARGS__ )
#define BOX_BRUSH( RelativePath, ... ) FSlateBoxBrush( Style->RootToContentDir( RelativePath, TEXT(".png") ), __VA_ARGS__ )
#define BORDER_BRUSH( RelativePath, ... ) FSlateBorderBrush( Style->RootToContentDir( RelativePath, TEXT(".png") ), __VA_ARGS__ )

TSharedPtr<FSlateStyleSet> FUnLuaStyle::StyleInst = NULL;

void FUnLuaStyle::Initialize()
{
	if (!StyleInst.IsValid())
	{
		StyleInst = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*StyleInst);
	}
}

void FUnLuaStyle::Shutdown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleInst);
	ensure(StyleInst.IsUnique());
	StyleInst.Reset();
}

FName FUnLuaStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT("UnLuaStyle"));
	return StyleSetName;
}

TSharedRef< FSlateStyleSet > FUnLuaStyle::Create()
{
	TSharedRef< FSlateStyleSet > Style = MakeShareable(new FSlateStyleSet("UnLuaStyle"));
	Style->SetContentRoot(FPaths::EngineContentDir() / TEXT("Editor/Slate/Common"));

	Style->Set("Black", new BOX_BRUSH(TEXT("Common/FlatButton"), 2.0f / 8.0f, FLinearColor(0.125f, 0.125f, 0.125f, 0.8f)));
	Style->Set("Yellow", new BOX_BRUSH(TEXT("Common/FlatButton"), 2.0f / 8.0f, FLinearColor(0.87514, 0.42591, 0.07383)));
	Style->Set("Blue", new BOX_BRUSH(TEXT("Common/FlatButton"), 2.0f / 8.0f, FLinearColor(0.10363, 0.53564, 0.7372)));

	return Style;
}

#undef IMAGE_BRUSH
#undef BOX_BRUSH
#undef BORDER_BRUSH

void FUnLuaStyle::ReloadTextures()
{
	FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
}

const ISlateStyle& FUnLuaStyle::Get()
{
	return *StyleInst;
}
