// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "UnLuaMemAnalyzerPanel.h"
#include "EditorStyleSet.h"
#include "SMemSnapshotToggle.h"
#include "Widgets/SWindow.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/InvalidateWidgetReason.h"

void SUnLuaMemAnalyzerPanel::Construct(const SUnLuaMemAnalyzerPanel::FArguments& InArgs)
{

}

TSharedRef<class SDockTab> SUnLuaMemAnalyzerPanel::GetSDockTab()
{
	TabIsOpening = true;

	UpdateShowingRoot();

	// Init TreeViewWidget
	SAssignNew(TreeViewWidget, STreeView<TSharedPtr<FUnLuaMemInfoNode>>)
		.ItemHeight(800)
		.TreeItemsSource(&ShowingNodeList)
		.OnGenerateRow(this, &SUnLuaMemAnalyzerPanel::OnGenerateRow)
		.OnGetChildren(this, &SUnLuaMemAnalyzerPanel::OnGetChildrenRaw)
		.SelectionMode(ESelectionMode::None)
		.HighlightParentNodesForSelection(true)
		.HeaderRow
		(
			SNew(SHeaderRow)
			+ SHeaderRow::Column("Name").DefaultLabel(FText::FromName("Name")).HAlignHeader(HAlign_Fill)
			+ SHeaderRow::Column("Size").DefaultLabel(FText::FromName("Size")).FixedWidth(80)
			+ SHeaderRow::Column("Type").DefaultLabel(FText::FromName("Type")).FixedWidth(80)
			+ SHeaderRow::Column("Count").DefaultLabel(FText::FromName("Count")).FixedWidth(80)
			+ SHeaderRow::Column("Level").DefaultLabel(FText::FromName("Level")).FixedWidth(80)

			//+ SHeaderRow::Column("Calls").DefaultLabel(FText::FromName("Calls")).FixedWidth(60)
			//.SortMode_Lambda([&]() { return FUnLuaMonitor::GetInstance()->GetSortMode() == Calls ? EColumnSortMode::Descending : EColumnSortMode::None; })
			//.OnSort_Lambda([&](const EColumnSortPriority::Type SortPriority, const FName& ColumnName, const EColumnSortMode::Type NewSortMode)
			//{
			//	FUnLuaMonitor::GetInstance()->SetSortMode(Calls);
			//})
		);


	SAssignNew(DockTab, SDockTab)
	.Icon(FEditorStyle::GetBrush("Kismet.Tabs.Palette"))
	.Label(FText::FromName("UnLuaMemAnalyzer"))
	[
		SNew(SVerticalBox)
		+ SVerticalBox::Slot().AutoHeight()
		[
			SNew(SBorder).HAlign(HAlign_Center)
			.BorderImage(FEditorStyle::GetBrush("ToolPanel.GroupBorder"))
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot().HAlign(HAlign_Center).VAlign(VAlign_Center).AutoWidth()
				[
					SNew(SButton)
					.ContentPadding(2.0)
					.IsFocusable(false)
					.OnClicked(this, &SUnLuaMemAnalyzerPanel::OnSnapshotBtnClicked)
					[
						SNew(STextBlock)
						.Text(FText::FromName("Snapshot"))
					]
				]

				+ SHorizontalBox::Slot().HAlign(HAlign_Center).VAlign(VAlign_Center).AutoWidth()
				[
					SNew(SButton)
					.ContentPadding(2.0)
					.IsFocusable(false)
					.OnClicked(this, &SUnLuaMemAnalyzerPanel::OnGCBtnClicked)
					[
						SNew(STextBlock)
						.Text(FText::FromName("GC"))
					]
				]

				+ SHorizontalBox::Slot().HAlign(HAlign_Center).VAlign(VAlign_Center).AutoWidth()
				[
					SAssignNew(AndBtn, SButton)
					.ForegroundColor(FSlateColor::UseForeground())
					.ButtonStyle(&GetToggleStyle(SOP_AND))
					.ContentPadding(2.0)
					.IsFocusable(false)
					.OnClicked_Lambda([this]()
					{
						return OnSOPBtnClicked(ESnapshotOp::SOP_AND);
					})
					[
						SNew(STextBlock)
						.Text(FText::FromName("AND"))
					]
				]

				+ SHorizontalBox::Slot().HAlign(HAlign_Center).VAlign(VAlign_Center).AutoWidth()
				[
					SAssignNew(OrBtn, SButton)
					.ForegroundColor(FSlateColor::UseForeground())
					.ButtonStyle(&GetToggleStyle(SOP_OR))
					.ContentPadding(2.0)
					.IsFocusable(false)
					.OnClicked_Lambda([this]()
					{
						return OnSOPBtnClicked(ESnapshotOp::SOP_OR);
					})
					[
						SNew(STextBlock)
						.Text(FText::FromName("OR"))
					]
				]

				+ SHorizontalBox::Slot().HAlign(HAlign_Center).VAlign(VAlign_Center).AutoWidth()
				[
					SAssignNew(XorBtn, SButton)
					.ForegroundColor(FSlateColor::UseForeground())
					.ButtonStyle(&GetToggleStyle(SOP_XOR))
					.ContentPadding(2.0)
					.IsFocusable(false)
					.OnClicked_Lambda([this]()
					{
						return OnSOPBtnClicked(ESnapshotOp::SOP_XOR);
					})
					[
						SNew(STextBlock)
						.Text(FText::FromName("XOR"))
					]
				]
			]
		]

		+ SVerticalBox::Slot().AutoHeight()
		[
			SAssignNew(MemToggleListWidget, SVerticalBox)
		]

		+ SVerticalBox::Slot().FillHeight(1.f)
		[
			SNew(SBorder)
			.Padding(0)
			.BorderImage(FCoreStyle::Get().GetBrush("ToolPanel.GroupBorder"))
			[
				TreeViewWidget.ToSharedRef()
			]
		]
	];
	DockTab->SetOnTabClosed(SDockTab::FOnTabClosedCallback::CreateRaw(this, &SUnLuaMemAnalyzerPanel::OnCloseTab));
	return DockTab.ToSharedRef();
}

TSharedRef<ITableRow> SUnLuaMemAnalyzerPanel::OnGenerateRow(TSharedPtr<FUnLuaMemInfoNode> MINode, const TSharedRef<STableViewBase>& OwnerTable)
{
	return
	SNew(STableRow<TSharedPtr<FUnLuaMemInfoNode>>, OwnerTable)
	[
		SNew(SHeaderRow)
		+ SHeaderRow::Column("Name").DefaultLabel(FText::FromString(MINode->desc))
		.DefaultTooltip(FText::FromString(MINode->desc)).HAlignHeader(HAlign_Fill)
		+SHeaderRow::Column("Size").FixedWidth(80).DefaultLabel(FText::AsNumber(MINode->totalsize))
		+SHeaderRow::Column("Type").FixedWidth(80).DefaultLabel(FText::FromString(MINode->type))
		+SHeaderRow::Column("Count").FixedWidth(80).DefaultLabel(FText::AsNumber(MINode->count))
		+SHeaderRow::Column("Level").FixedWidth(80).DefaultLabel(FText::AsNumber(MINode->level))
	];
}

void SUnLuaMemAnalyzerPanel::OnGetChildrenRaw(TSharedPtr<FUnLuaMemInfoNode> MINode, TArray<TSharedPtr<FUnLuaMemInfoNode>>& OutChildren)
{
	if (MINode)
	{
		OutChildren = MINode->children;
	}
}

void SUnLuaMemAnalyzerPanel::UpdateShowingRoot()
{
	CurMIRoot = FUnLuaMemAnalyzer::GetInstance()->GetShowingRoot();
	if (CurMIRoot)
	{
		ShowingNodeList = { CurMIRoot };
	}
	else
	{
		ShowingNodeList = {};
	}
}

void SUnLuaMemAnalyzerPanel::DeferredTick(float DeltaTime)
{
	if (CurMIRoot != FUnLuaMemAnalyzer::GetInstance()->GetShowingRoot())
	{
		UpdateShowingRoot();
	}

	if (TreeViewWidget.IsValid())
	{
		TreeViewWidget->RequestTreeRefresh();
	}

	TSharedPtr<SWindow> Window = DockTab->GetParentWindow();
	if (Window && FUnLuaMemAnalyzer::GetInstance()->NeedRefresh())
	{
		int32 Count = FUnLuaMemAnalyzer::GetInstance()->GetSnapshotNum();
		MemToggleListWidget->ClearChildren();
		int32 ColNum = Window->GetSizeInScreen().X / (140 * Window->GetNativeWindow()->GetDPIScaleFactor());
		int32 RowNum = FMath::CeilToInt(Count / ((float)ColNum));
		for (int32 r = 0; r < RowNum; r++)
		{
			TSharedRef<SHorizontalBox> Row = SNew(SHorizontalBox);
			for (int32 c = 0; c < ColNum; c++)
			{
				int32 Index = ColNum * r + c;
				if (Index < Count)
				{
					Row->AddSlot().HAlign(HAlign_Left).VAlign(VAlign_Center).FillWidth(120).Padding(10)
					[
						SNew(SMemSnapshotToggle)
						.SnapshotIndex(Index)
						//.OnClicked_Lambda([this]()
						//{
						//	return FReply::Handled();
						//})
						//.OnDoubleClicked_Lambda([this, Index]()
						//{
						//	return FReply::Handled();
						//})
						//.OnDeleted_Lambda([this]()
						//{
						//})
						//.OnCancelled_Lambda([this]()
						//{
						//})
					];
				}
			}

			MemToggleListWidget->AddSlot().HAlign(HAlign_Left).VAlign(VAlign_Center).Padding(5)
			[
				Row
			];
		}
		FUnLuaMemAnalyzer::GetInstance()->OnRefresh();
	}

	AndBtn->SetButtonStyle(&GetToggleStyle(SOP_AND));
	OrBtn->SetButtonStyle(&GetToggleStyle(SOP_OR));
	XorBtn->SetButtonStyle(&GetToggleStyle(SOP_XOR));
}

void SUnLuaMemAnalyzerPanel::OnCloseTab(TSharedRef<SDockTab> Tab)
{
	TabIsOpening = false;
}

FReply SUnLuaMemAnalyzerPanel::OnSnapshotBtnClicked()
{
	FUnLuaMemAnalyzer::GetInstance()->Snapshot();
	return FReply::Handled();
}

FReply SUnLuaMemAnalyzerPanel::OnGCBtnClicked()
{
	FUnLuaMemAnalyzer::GetInstance()->ForceLuaGC();
	return FReply::Handled();
}

FReply SUnLuaMemAnalyzerPanel::OnSOPBtnClicked(ESnapshotOp ESOP)
{
	FUnLuaMemAnalyzer::GetInstance()->OnSnapshotOperate(ESOP);
	return FReply::Handled();
}

// FlatButton.Success	绿色
// FlatButton.Danger	红色
// FlatButton.Light		白色
// FlatButton.Info		蓝色
// FlatButton.Warning	黄色
// FlatButton.Primary	深蓝色
// FlatButton.Dark		黑色
const FButtonStyle& SUnLuaMemAnalyzerPanel::GetToggleStyle(ESnapshotOp ESOP)
{
	if (FUnLuaMemAnalyzer::GetInstance()->IsOperateMode(ESOP))
	{
		return FEditorStyle::Get().GetWidgetStyle<FButtonStyle>("FlatButton.Success");
	} 
	else
	{
		return FEditorStyle::Get().GetWidgetStyle<FButtonStyle>("FlatButton.Dark");
	}
}
