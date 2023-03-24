// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "UnLuaProfilerBase.h"
#include "UnLuaMemAnalyzer/UnLuaMemInfoNode.h"
#include "UnLuaMemAnalyzer/UnLuaMemAnalyzer.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/Views/STreeView.h"
#include "Widgets/Docking/SDockTab.h"

class SUnLuaMemAnalyzerPanel : public SCompoundWidget
{
public:

	SLATE_BEGIN_ARGS(SUnLuaMemAnalyzerPanel) {}
	SLATE_END_ARGS()

	void Construct(const SUnLuaMemAnalyzerPanel::FArguments& InArgs);

	TSharedRef<class SDockTab> GetSDockTab();

	void DeferredTick(float DeltaTime);

	bool IsOpening() { return TabIsOpening; }

private:
	TSharedRef<ITableRow> OnGenerateRow(TSharedPtr<FUnLuaMemInfoNode> MINode, const TSharedRef<STableViewBase>& OwnerTable);

	void OnGetChildrenRaw(TSharedPtr<FUnLuaMemInfoNode> MINode, TArray<TSharedPtr<FUnLuaMemInfoNode>>& OutChildren);

	void UpdateShowingRoot();

	void OnCloseTab(TSharedRef<SDockTab> Tab);

	FReply OnSnapshotBtnClicked();

	FReply OnGCBtnClicked();

	void OnRefreshSOPToggleStyle();

	FReply OnSOPBtnClicked(ESnapshotOp ESOP);

	const FButtonStyle& GetToggleStyle(ESnapshotOp ESOP);

private:

	TSharedPtr<SDockTab> DockTab;

	TSharedPtr<SVerticalBox> MemToggleListWidget;

	TSharedPtr<STreeView<TSharedPtr<FUnLuaMemInfoNode>>> TreeViewWidget;

	TArray<TSharedPtr<FUnLuaMemInfoNode>> ShowingNodeList;

	TSharedPtr<FUnLuaMemInfoNode> CurMIRoot;

	bool TabIsOpening = false;

	TSharedPtr<SButton> AndBtn;

	TSharedPtr<SButton> OrBtn;

	TSharedPtr<SButton> XorBtn;
};

