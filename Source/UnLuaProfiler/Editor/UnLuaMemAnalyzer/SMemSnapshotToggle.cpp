// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "SMemSnapshotToggle.h"
#include "Styles/UnLuaStyle.h"
#include "EditorStyleSet.h"
#include "UnLuaMemAnalyzer/UnLuaMemAnalyzer.h"
#include "Widgets/SBoxPanel.h"
#include "Styling/SlateStyle.h"
#include "Widgets/Images/SImage.h"
#include "Widgets/Layout/SSpacer.h"
#include "Widgets/Text/STextBlock.h"

SMemSnapshotToggle::SMemSnapshotToggle()
{

}

/**
 * Construct this widget
 *
 * @param	InArgs	The declaration data for this widget
 */
void SMemSnapshotToggle::Construct(const FArguments& InArgs)
{
	TSharedPtr<FUnLuaMemSnapshot> snapshot = FUnLuaMemAnalyzer::GetInstance()->GetSnapshot(InArgs._SnapshotIndex);
	FString ToggleLabel = snapshot ? FString::Printf(TEXT("%.2f %s"), snapshot->GetTotalSizeMB(), *snapshot->GetSnapTimeStr()) : "Snapshot Missing";
	SBorder::Construct(SBorder::FArguments()
		//.ContentScale(InArgs._ContentScale)
		//.DesiredSizeScale(InArgs._DesiredSizeScale)
		//.BorderBackgroundColor(InArgs._ButtonColorAndOpacity)
		//.ForegroundColor(InArgs._ForegroundColor)
		.BorderImage(this, &SMemSnapshotToggle::GetBorder)
		//.HAlign(InArgs._HAlign)
		//.VAlign(InArgs._VAlign)
		//.Padding(TAttribute<FMargin>(this, &SButton::GetCombinedPadding))
		//.ShowEffectWhenDisabled(TAttribute<bool>(this, &SButton::GetShowDisabledEffect))
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot().HAlign(HAlign_Center).VAlign(VAlign_Center).AutoWidth()
			[
				SNew(STextBlock)
				.Text(FText::FromString(ToggleLabel))
			]
	
			+ SHorizontalBox::Slot().HAlign(HAlign_Center).VAlign(VAlign_Top).AutoWidth()
			[
				SNew(SVerticalBox)
				+ SVerticalBox::Slot().HAlign(HAlign_Center).VAlign(VAlign_Top).AutoHeight()
				[
					SNew(SButton)
					.ButtonStyle(FEditorStyle::Get(), "NoBorder")
					.OnClicked_Lambda([this]()
					{
						FUnLuaMemAnalyzer::GetInstance()->OnDeleteSnapshot(SnapshotIndex);
						return FReply::Handled();
					})
					[
						SNew(SImage)
						.Image(FEditorStyle::GetBrush("Cross"))
					]
				]

				+ SVerticalBox::Slot().HAlign(HAlign_Center).VAlign(VAlign_Center).AutoHeight()
				[
					SNew(SSpacer)
				]
			]
		]
	);

	NormalImage = FUnLuaStyle::Get().GetBrush("Black");

	SelectedImage = FUnLuaStyle::Get().GetBrush("Yellow");

	Invalidate(EInvalidateWidget::Layout);

	SnapshotIndex = InArgs._SnapshotIndex;
	OnClicked = InArgs._OnClicked;
	OnDoubleClicked = InArgs._OnDoubleClicked;
	OnDeleted = InArgs._OnDeleted;
	OnCancelled = InArgs._OnCancelled;
}

int32 SMemSnapshotToggle::OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	const FSlateBrush* BrushResource = GetBorder();

	if (BrushResource && BrushResource->DrawAs != ESlateBrushDrawType::NoDrawType)
	{
		FSlateDrawElement::MakeBox(
			OutDrawElements,
			LayerId,
			AllottedGeometry.ToPaintGeometry(),
			BrushResource,
			ESlateDrawEffect::None,
			BrushResource->GetTint(InWidgetStyle) * InWidgetStyle.GetColorAndOpacityTint() * BorderBackgroundColor.Get().GetColor(InWidgetStyle)
		);
	}

	return SCompoundWidget::OnPaint(Args, AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle, true);
}

/** @return An image that represents this button's border*/
const FSlateBrush* SMemSnapshotToggle::GetBorder() const
{
	if (FUnLuaMemAnalyzer::GetInstance()->IsSelectedSnapshot(SnapshotIndex))
	{
		return SelectedImage;
	} 
	else
	{
		return NormalImage;
	}
}

FReply SMemSnapshotToggle::OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	FReply Reply = FReply::Handled();
	if (!FUnLuaMemAnalyzer::GetInstance()->IsSelectedSnapshot(SnapshotIndex))
	{
		FUnLuaMemAnalyzer::GetInstance()->OnSelectSnapshot(SnapshotIndex);
		if (OnClicked.IsBound())
		{
			Reply = OnClicked.Execute();
		}
	}
	else
	{
		FUnLuaMemAnalyzer::GetInstance()->OnCancelOperate(SnapshotIndex);
		OnCancelled.ExecuteIfBound();
	}

	return Reply;
}

FReply SMemSnapshotToggle::OnMouseButtonDoubleClick(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent)
{
	FUnLuaMemAnalyzer::GetInstance()->ShowSnapshot(SnapshotIndex);
	FReply Reply = FReply::Handled();
	if (OnDoubleClicked.IsBound())
	{
		Reply = OnDoubleClicked.Execute();
	}
	return Reply;
}

FVector2D SMemSnapshotToggle::ComputeDesiredSize(float LayoutScaleMultiplier) const
{
	return SBorder::ComputeDesiredSize(LayoutScaleMultiplier);
}
