// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "UnLuaProfilerBase.h"
#include "UnLuaMonitor/UnLuaTraceInfoNode.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Input/SSpinBox.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/Views/STreeView.h"
#include "Widgets/Docking/SDockTab.h"

class SUnLuaMonitorPanel : public SCompoundWidget
{
public:

	SLATE_BEGIN_ARGS(SUnLuaMonitorPanel) {}
	SLATE_END_ARGS()

	void Construct(const SUnLuaMonitorPanel::FArguments& InArgs);

    TSharedRef<class SDockTab> GetSDockTab();

	TSharedRef<ITableRow> OnGenerateRow(TSharedPtr<FUnLuaTraceInfoNode> TINode, const TSharedRef<STableViewBase>& OwnerTable);

	void OnGetChildrenRaw(TSharedPtr<FUnLuaTraceInfoNode> Parent, TArray<TSharedPtr<FUnLuaTraceInfoNode>>& OutChildren);

	void DeferredTick(float DeltaTime);

	bool IsOpening() { return TabIsOpening; }

private:
	FReply OnForwardBtnClicked();

	FReply OnClearBtnClicked();

	FReply OnPrevFrameBtnClicked();

	FReply OnNextFrameBtnClicked();

	const FSlateBrush* GetPrevFrameIcon() const;

	const FSlateBrush* GetForwardIcon() const;

	const FSlateBrush* GetNextFrameIcon() const;

	void UpdateShowingRoot();

	void OnModeChanged(float InMode);

	void OnGenerateFrameController();

	void OnRemoveFrameController();

	int32 OnGetMaxDepth() const;

	void OnMaxDepthChanged(int32 Depth);

	FText OnGetTotalFrameText() const;

	int32 OnGetCurFrameIndex() const;

	void OnCurFrameIndexChanged(int32 Index);

	void OnCloseTab(TSharedRef<SDockTab> Tab);

private:
	TSharedPtr<STreeView<TSharedPtr<FUnLuaTraceInfoNode>>> TreeViewWidget;

	TSharedPtr<FUnLuaTraceInfoNode> CurTIRoot;

	TArray<TSharedPtr<FUnLuaTraceInfoNode>> ShowingNodeList;

	TSharedPtr<SHorizontalBox> ControllerBar;

	TSharedPtr<SButton> PrevFrameBtn;

	TSharedPtr<SButton> NextFrameBtn;

	TSharedPtr<SSpinBox<int32>> CurFrameSpin;

	TSharedPtr<STextBlock> TotalFrameText;

	UnLuaMonitorMode MonitorMode = Total;

	float ElapsedTime = 0.f;

	const static int32 COL_WIDTH = 80;

	const float UPDATE_INTERVAL = 0.5f;

	bool TabIsOpening = false;
};
