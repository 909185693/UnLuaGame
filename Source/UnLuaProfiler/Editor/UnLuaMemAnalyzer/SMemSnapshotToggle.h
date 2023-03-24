// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Misc/Attribute.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Layout/SBorder.h"

class FPaintArgs;

class SMemSnapshotToggle : public SBorder
{
public:

	SLATE_BEGIN_ARGS(SMemSnapshotToggle)
		: _Content()
		, _ButtonStyle(&FCoreStyle::Get().GetWidgetStyle< FButtonStyle >("Button"))
		, _SnapshotIndex(-1)
		{

		}

		/** Slot for this button's content (optional) */
		SLATE_DEFAULT_SLOT(FArguments, Content)

		SLATE_STYLE_ARGUMENT(FButtonStyle, ButtonStyle)

		SLATE_ARGUMENT(int32, SnapshotIndex)

		SLATE_EVENT(FOnClicked, OnClicked)

		SLATE_EVENT(FOnClicked, OnDoubleClicked)

		SLATE_EVENT(FSimpleDelegate, OnDeleted)
			
		SLATE_EVENT(FSimpleDelegate, OnCancelled)

		SLATE_END_ARGS()

	SMemSnapshotToggle();

	/** @return An image that represents this button's border*/
	virtual const FSlateBrush* GetBorder() const;

	/**
	 * Construct this widget
	 *
	 * @param	InArgs	The declaration data for this widget
	 */
	void Construct(const FArguments& InArgs);

public:

	// SWidget overrides
	virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;

	virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	virtual FReply OnMouseButtonDoubleClick(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent) override;

private:

	virtual FVector2D ComputeDesiredSize(float) const override;

protected:

	const FSlateBrush* NormalImage;

	const FSlateBrush* SelectedImage;

	FOnClicked OnClicked;

	FOnClicked OnDoubleClicked;

	FSimpleDelegate OnDeleted;

	FSimpleDelegate OnCancelled;

	int32 SnapshotIndex = -1;
};
