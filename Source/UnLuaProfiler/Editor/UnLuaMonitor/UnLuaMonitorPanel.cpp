// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "UnLuaMonitorPanel.h"
#include "UnLuaMonitor/UnLuaMonitor.h"
#include "EditorStyleSet.h"
#include "Widgets/Images/SImage.h"
#include "Widgets/Layout/SSpacer.h"
#include "Widgets/Input/SCheckBox.h"
#include "Widgets/Layout/SScrollBox.h"
#include "Widgets/Input/SNumericDropDown.h"

#define LOCTEXT_NAMESPACE "UnLuaProfiler"

void SUnLuaMonitorPanel::Construct(const SUnLuaMonitorPanel::FArguments& InArgs)
{

}

TSharedRef<class SDockTab> SUnLuaMonitorPanel::GetSDockTab()
{
	TabIsOpening = true;

	FUnLuaMonitor::GetInstance()->SetMonitorMode(MonitorMode);

	UpdateShowingRoot();


	TArray<SNumericDropDown<float>::FNamedValue> NamedValuesForMonitorMode;
	NamedValuesForMonitorMode.Add(SNumericDropDown<float>::FNamedValue((float)UnLuaMonitorMode::PerFrame, FText::FromName("PerFrame"), FText::FromName("PerFrameRecord")));
	NamedValuesForMonitorMode.Add(SNumericDropDown<float>::FNamedValue((float)UnLuaMonitorMode::Total, FText::FromName("Total"), FText::FromName("RecordTotalInfo")));
	NamedValuesForMonitorMode.Add(SNumericDropDown<float>::FNamedValue((float)UnLuaMonitorMode::Statistics, FText::FromName("Statistics"), FText::FromName("Tile all node")));


	// Init TreeViewWidget
	SAssignNew(TreeViewWidget, STreeView<TSharedPtr<FUnLuaTraceInfoNode>>)
		.ItemHeight(800)
		.TreeItemsSource(&ShowingNodeList)
		.OnGenerateRow(this, &SUnLuaMonitorPanel::OnGenerateRow)
		.OnGetChildren(this, &SUnLuaMonitorPanel::OnGetChildrenRaw)
		.SelectionMode(ESelectionMode::None)
		.HighlightParentNodesForSelection(true)
		.HeaderRow
		(
			SNew(SHeaderRow)
			+ SHeaderRow::Column("Name").DefaultLabel(FText::FromName("Name")).HAlignHeader(HAlign_Fill)
			+ SHeaderRow::Column("TotalTime(ms)").DefaultLabel(FText::FromName("TotalTime(ms)")).FixedWidth(90)
			.SortMode_Lambda([&]() { return FUnLuaMonitor::GetInstance()->GetSortMode() == TotalTime ? EColumnSortMode::Descending : EColumnSortMode::None; })
			.OnSort_Lambda([&](const EColumnSortPriority::Type SortPriority, const FName& ColumnName, const EColumnSortMode::Type NewSortMode)
			{
				FUnLuaMonitor::GetInstance()->SetSortMode(TotalTime);
			})
			+ SHeaderRow::Column("TotalTime(%)").DefaultLabel(FText::FromName("TotalTime(%)")).FixedWidth(COL_WIDTH)
			.SortMode_Lambda([&]() { return FUnLuaMonitor::GetInstance()->GetSortMode() == TotalTime ? EColumnSortMode::Descending : EColumnSortMode::None; })
			.OnSort_Lambda([&](const EColumnSortPriority::Type SortPriority, const FName& ColumnName, const EColumnSortMode::Type NewSortMode)
			{
				FUnLuaMonitor::GetInstance()->SetSortMode(TotalTime);
			})

			+ SHeaderRow::Column("SelfTime(ms)").DefaultLabel(FText::FromName("SelfTime(ms)")).FixedWidth(COL_WIDTH)
			.SortMode_Lambda([&]() { return FUnLuaMonitor::GetInstance()->GetSortMode() == SelfTime ? EColumnSortMode::Descending : EColumnSortMode::None; })
			.OnSort_Lambda([&](const EColumnSortPriority::Type SortPriority, const FName& ColumnName, const EColumnSortMode::Type NewSortMode)
			{
				FUnLuaMonitor::GetInstance()->SetSortMode(SelfTime);
			})
			+ SHeaderRow::Column("SelfTime(%)").DefaultLabel(FText::FromName("SelfTime(%)")).FixedWidth(COL_WIDTH)
			.SortMode_Lambda([&]() { return FUnLuaMonitor::GetInstance()->GetSortMode() == SelfTime ? EColumnSortMode::Descending : EColumnSortMode::None; })
			.OnSort_Lambda([&](const EColumnSortPriority::Type SortPriority, const FName& ColumnName, const EColumnSortMode::Type NewSortMode)
			{
				FUnLuaMonitor::GetInstance()->SetSortMode(SelfTime);
			})

			+ SHeaderRow::Column("Average(ms)").DefaultLabel(FText::FromName("Average(ms)")).FixedWidth(COL_WIDTH)
			.SortMode_Lambda([&]() { return FUnLuaMonitor::GetInstance()->GetSortMode() == Average ? EColumnSortMode::Descending : EColumnSortMode::None; })
			.OnSort_Lambda([&](const EColumnSortPriority::Type SortPriority, const FName& ColumnName, const EColumnSortMode::Type NewSortMode)
			{
				FUnLuaMonitor::GetInstance()->SetSortMode(Average);
			})

			+ SHeaderRow::Column("Alloc(kb)").DefaultLabel(FText::FromName("Alloc(kb)")).FixedWidth(COL_WIDTH)
			.SortMode_Lambda([&]() { return FUnLuaMonitor::GetInstance()->GetSortMode() == Alloc ? EColumnSortMode::Descending : EColumnSortMode::None; })
			.OnSort_Lambda([&](const EColumnSortPriority::Type SortPriority, const FName& ColumnName, const EColumnSortMode::Type NewSortMode)
			{
				FUnLuaMonitor::GetInstance()->SetSortMode(Alloc);
			})
			+ SHeaderRow::Column("Alloc(%)").DefaultLabel(FText::FromName("Alloc(%)")).FixedWidth(60)
			.SortMode_Lambda([&]() { return FUnLuaMonitor::GetInstance()->GetSortMode() == Alloc ? EColumnSortMode::Descending : EColumnSortMode::None; })
			.OnSort_Lambda([&](const EColumnSortPriority::Type SortPriority, const FName& ColumnName, const EColumnSortMode::Type NewSortMode)
			{
				FUnLuaMonitor::GetInstance()->SetSortMode(Alloc);
			})

			+ SHeaderRow::Column("GC(kb)").DefaultLabel(FText::FromName("GC(kb)")).FixedWidth(60)
			.SortMode_Lambda([&]() { return FUnLuaMonitor::GetInstance()->GetSortMode() == GC ? EColumnSortMode::Descending : EColumnSortMode::None; })
			.OnSort_Lambda([&](const EColumnSortPriority::Type SortPriority, const FName& ColumnName, const EColumnSortMode::Type NewSortMode)
			{
				FUnLuaMonitor::GetInstance()->SetSortMode(GC);
			})
			+ SHeaderRow::Column("GC(%)").DefaultLabel(FText::FromName("GC(%)")).FixedWidth(50)
			.SortMode_Lambda([&]() { return FUnLuaMonitor::GetInstance()->GetSortMode() == GC ? EColumnSortMode::Descending : EColumnSortMode::None; })
			.OnSort_Lambda([&](const EColumnSortPriority::Type SortPriority, const FName& ColumnName, const EColumnSortMode::Type NewSortMode)
			{
				FUnLuaMonitor::GetInstance()->SetSortMode(GC);
			})

			+ SHeaderRow::Column("Calls").DefaultLabel(FText::FromName("Calls")).FixedWidth(60)
			.SortMode_Lambda([&]() { return FUnLuaMonitor::GetInstance()->GetSortMode() == Calls ? EColumnSortMode::Descending : EColumnSortMode::None; })
			.OnSort_Lambda([&](const EColumnSortPriority::Type SortPriority, const FName& ColumnName, const EColumnSortMode::Type NewSortMode)
			{
				FUnLuaMonitor::GetInstance()->SetSortMode(Calls);
			})
		);


	SAssignNew(ControllerBar, SHorizontalBox);
	ControllerBar->AddSlot().HAlign(HAlign_Left).VAlign(VAlign_Center).AutoWidth()
	[
		SNew(SNumericDropDown<float>)
			.LabelText(FText::FromName("Mode:"))
			.bShowNamedValue(true)
			.DropDownValues(NamedValuesForMonitorMode)
			.IsEnabled(true)
			.Value_Lambda([this]() { return (float)MonitorMode; })
			.OnValueChanged(this, &SUnLuaMonitorPanel::OnModeChanged)
	];
	ControllerBar->AddSlot()
	[
		SNew(SSpacer)
	];
	ControllerBar->AddSlot().HAlign(HAlign_Center).VAlign(VAlign_Center).AutoWidth()
	[
		SNew(SButton)
		.ButtonStyle(FEditorStyle::Get(), "NoBorder")																// 无底图以免按钮发白
		.ContentPadding(2.0)
		.IsFocusable(false)
		.OnClicked(this, &SUnLuaMonitorPanel::OnForwardBtnClicked)
		[
			SNew(SImage)
			.Image(this, &SUnLuaMonitorPanel::GetForwardIcon)
		]
	];
	ControllerBar->AddSlot()
	[
		SNew(SSpacer)
	];

	ControllerBar->AddSlot().HAlign(HAlign_Right).VAlign(VAlign_Center).AutoWidth()
	[
		SNew(STextBlock)
		.Text(FText::FromName("Depth: "))
	];

	ControllerBar->AddSlot().HAlign(HAlign_Right).VAlign(VAlign_Center).AutoWidth()
	[
		SNew(SSpinBox<int32>)
		.Delta(1)
		.MinValue(1)
		.MaxValue(1000)
		.Value(this, &SUnLuaMonitorPanel::OnGetMaxDepth)
		.OnValueChanged(this, &SUnLuaMonitorPanel::OnMaxDepthChanged)
	];

	ControllerBar->AddSlot().HAlign(HAlign_Right).VAlign(VAlign_Center).AutoWidth()
	[
		SNew(SButton)
		.ButtonStyle(FEditorStyle::Get(), "NoBorder")																// 无底图以免按钮发白
		.ContentPadding(2.0)
		.IsFocusable(false)
		.OnClicked(this, &SUnLuaMonitorPanel::OnClearBtnClicked)
		.ToolTipText(FText::FromName("Clear and stop monitor"))
		[
			SNew(SImage)
			.Image(FEditorStyle::GetBrush("Cross"))
		]
	];

	OnGenerateFrameController();


	TSharedPtr<SDockTab> Tab;
	SAssignNew(Tab, SDockTab)
	.Icon(FEditorStyle::GetBrush("Kismet.Tabs.Palette"))
	.Label(FText::FromName("UnLuaMonitor"))
	[
		SNew(SVerticalBox)
		+ SVerticalBox::Slot().AutoHeight()
		[
			SNew(SBorder)
			.BorderImage(FEditorStyle::GetBrush("ToolPanel.GroupBorder"))
			//.BorderBackgroundColor(FLinearColor(.50f, .50f, .50f, 1.0f))
			[
				ControllerBar.ToSharedRef()
			]
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
	Tab->SetOnTabClosed(SDockTab::FOnTabClosedCallback::CreateRaw(this, &SUnLuaMonitorPanel::OnCloseTab));
	return Tab.ToSharedRef();
}

TSharedRef<ITableRow> SUnLuaMonitorPanel::OnGenerateRow(TSharedPtr<FUnLuaTraceInfoNode> TINode, const TSharedRef<STableViewBase>& OwnerTable)
{
	return
	SNew(STableRow<TSharedPtr<FUnLuaTraceInfoNode>>, OwnerTable)
	[
		SNew(SHeaderRow)
		+ SHeaderRow::Column("Name").DefaultLabel(FText::FromString(TINode->ID))
		.DefaultTooltip(FText::FromString(TINode->ID)).HAlignHeader(HAlign_Fill)
		+SHeaderRow::Column("TotalTime(ms)").FixedWidth(90).DefaultLabel(TAttribute<FText>::Create([=]() {
			return FText::AsNumber(TINode->TotalTime);
		}))
		+ SHeaderRow::Column("TotalTime(%)").FixedWidth(COL_WIDTH).DefaultLabel(TAttribute<FText>::Create([=]() {
			if (TINode->Parent && TINode->Parent->TotalTime > 0)
			{
				double d = TINode->TotalTime / TINode->Parent->TotalTime;
				return FText::AsPercent(d);
			} 
			else
			{
				return FText::AsPercent(0.f);
			}
		}))
		+ SHeaderRow::Column("SelfTime(ms)").FixedWidth(COL_WIDTH).DefaultLabel(TAttribute<FText>::Create([=]() {
			return FText::AsNumber(TINode->SelfTime);
		}))
		+ SHeaderRow::Column("SelfTime(%)").FixedWidth(COL_WIDTH).DefaultLabel(TAttribute<FText>::Create([=]() {
			if (TINode->Parent && TINode->Parent->TotalTime > 0)
			{
				double d = TINode->SelfTime / TINode->Parent->TotalTime;
				return FText::AsPercent(d);
			}
			return FText::AsPercent(0.f);
		}))
		+ SHeaderRow::Column("Avg(ms)").FixedWidth(COL_WIDTH).DefaultLabel(TAttribute<FText>::Create([=]() {
			return FText::AsNumber(TINode->Average);
		}))
		+ SHeaderRow::Column("Alloc(kb)").FixedWidth(COL_WIDTH).DefaultLabel(TAttribute<FText>::Create([=]() {
			return FText::AsNumber(TINode->AllocSize);
		}))
		+ SHeaderRow::Column("Alloc(%)").FixedWidth(60).DefaultLabel(TAttribute<FText>::Create([=]() {
			if (TINode->Parent && TINode->Parent->AllocSize > 0)
			{
				float p = TINode->AllocSize / TINode->Parent->AllocSize;
				return FText::AsPercent(p);
			}
			return FText::AsPercent(0.f);
		}))
		+ SHeaderRow::Column("GC(kb)").FixedWidth(60).DefaultLabel(TAttribute<FText>::Create([=]() {
			return FText::AsNumber(TINode->GCSize);
		}))
		+ SHeaderRow::Column("GC(%)").FixedWidth(50).DefaultLabel(TAttribute<FText>::Create([=]() {
			if (TINode->Parent && TINode->Parent->GCSize > 0)
			{
				float p = TINode->GCSize / TINode->Parent->GCSize;
				return FText::AsPercent(p);
			}
			return FText::AsPercent(0.f);
		}))
		+ SHeaderRow::Column("Calls").FixedWidth(60).DefaultLabel(TAttribute<FText>::Create([=]() {
			return FText::AsNumber(TINode->Count);
		}))
		
	];
}

void SUnLuaMonitorPanel::OnGetChildrenRaw(TSharedPtr<FUnLuaTraceInfoNode> TINode, TArray<TSharedPtr<FUnLuaTraceInfoNode>>& OutChildren)
{
	if (TINode)
	{
		OutChildren = TINode->Children;
	}
}

void SUnLuaMonitorPanel::UpdateShowingRoot()
{
	CurTIRoot = FUnLuaMonitor::GetInstance()->GetRoot();
	if (CurTIRoot)
	{
		ShowingNodeList = CurTIRoot->Children;
	}
	else
	{
		ShowingNodeList = {};
	}
}

void SUnLuaMonitorPanel::DeferredTick(float DeltaTime)
{
	FUnLuaMonitor::GetInstance()->Tick(DeltaTime);

	ElapsedTime += DeltaTime;

	if (MonitorMode == PerFrame || ElapsedTime > UPDATE_INTERVAL)
	{
		UpdateShowingRoot();

		if (TreeViewWidget.IsValid())
		{
			//TreeViewWidget->RebuildList();

			TreeViewWidget->RequestTreeRefresh();
		}

		ElapsedTime = 0.f;
	}
}

FReply SUnLuaMonitorPanel::OnForwardBtnClicked()
{
	FUnLuaMonitor::GetInstance()->OnForward();
	return FReply::Handled();
}

FReply SUnLuaMonitorPanel::OnClearBtnClicked()
{
	FUnLuaMonitor::GetInstance()->OnClear();
	return FReply::Handled();
}

FReply SUnLuaMonitorPanel::OnPrevFrameBtnClicked()
{
	FUnLuaMonitor::GetInstance()->SetCurFrameIndex(FUnLuaMonitor::GetInstance()->GetCurFrameIndex() - 1);
	return FReply::Handled();
}

FReply SUnLuaMonitorPanel::OnNextFrameBtnClicked()
{
	FUnLuaMonitor::GetInstance()->SetCurFrameIndex(FUnLuaMonitor::GetInstance()->GetCurFrameIndex() + 1);
	return FReply::Handled();
}

const FSlateBrush* SUnLuaMonitorPanel::GetPrevFrameIcon() const
{
	return  &FEditorStyle::Get().GetWidgetStyle<FButtonStyle>("Animation.Backward_Step").Normal;
}

const FSlateBrush* SUnLuaMonitorPanel::GetForwardIcon() const
{
	if (FUnLuaMonitor::GetInstance()->IsRuning())
	{
		return &FEditorStyle::Get().GetWidgetStyle<FButtonStyle>("Animation.Pause").Normal;
	}
	return  &FEditorStyle::Get().GetWidgetStyle<FButtonStyle>("Animation.Forward").Normal;
}

const FSlateBrush* SUnLuaMonitorPanel::GetNextFrameIcon() const
{
	return  &FEditorStyle::Get().GetWidgetStyle<FButtonStyle>("Animation.Forward_Step").Normal;
}

void SUnLuaMonitorPanel::OnModeChanged(float InMode)
{
	if (InMode > -1 && InMode < ((uint8)UnLuaMonitorMode::MAX))
	{
		if (!FMath::IsNearlyEqual((float)MonitorMode, InMode))
		{
			MonitorMode = (UnLuaMonitorMode)((uint8)InMode);
			FUnLuaMonitor::GetInstance()->SetMonitorMode(MonitorMode);
			switch (MonitorMode)
			{
			case PerFrame:
				OnGenerateFrameController();
				break;
			case Statistics:
				OnRemoveFrameController();
				break;
			case Total:
			default:
				OnRemoveFrameController();
				break;
			}
		}
	}
}

void SUnLuaMonitorPanel::OnGenerateFrameController()
{
	if (MonitorMode == PerFrame)
	{
		if (!PrevFrameBtn)
		{
			SAssignNew(PrevFrameBtn, SButton)
			.ButtonStyle(FEditorStyle::Get(), "NoBorder")																// 无底图以免按钮发白
			.ContentPadding(2.0)
			.IsFocusable(false)
			.OnClicked(this, &SUnLuaMonitorPanel::OnPrevFrameBtnClicked)
			[
				SNew(SImage)
				.Image(this, &SUnLuaMonitorPanel::GetPrevFrameIcon)
			];
		}

		if (!NextFrameBtn)
		{
			SAssignNew(NextFrameBtn, SButton)
			.ButtonStyle(FEditorStyle::Get(), "NoBorder")																// 无底图以免按钮发白
			.ContentPadding(2.0)
			.IsFocusable(false)
			.OnClicked(this, &SUnLuaMonitorPanel::OnNextFrameBtnClicked)
			[
				SNew(SImage)
				.Image(this, &SUnLuaMonitorPanel::GetNextFrameIcon)
			];
		}

		if (!CurFrameSpin)
		{
			SAssignNew(CurFrameSpin, SSpinBox<int32>)
			.Delta(1)
			.MinValue(0)
			.MaxValue(0x7FFFFFFF)
			.Value(this, &SUnLuaMonitorPanel::OnGetCurFrameIndex)
			.OnValueChanged(this, &SUnLuaMonitorPanel::OnCurFrameIndexChanged);
		}

		if (!TotalFrameText)
		{
			SAssignNew(TotalFrameText, STextBlock)
			.Text(this, &SUnLuaMonitorPanel::OnGetTotalFrameText);
		}

		if (ControllerBar.IsValid())
		{
			ControllerBar->InsertSlot(2).HAlign(HAlign_Center).VAlign(VAlign_Center).AutoWidth()
			[
				PrevFrameBtn.ToSharedRef()
			];
			ControllerBar->InsertSlot(4).HAlign(HAlign_Center).VAlign(VAlign_Center).AutoWidth()
			[
				NextFrameBtn.ToSharedRef()
			];
			ControllerBar->InsertSlot(6).HAlign(HAlign_Right).VAlign(VAlign_Center).AutoWidth()
			[
				CurFrameSpin.ToSharedRef()
			];
			ControllerBar->InsertSlot(7).HAlign(HAlign_Right).VAlign(VAlign_Center).AutoWidth()
			[
				TotalFrameText.ToSharedRef()
			];
		}
	}
}

void SUnLuaMonitorPanel::OnRemoveFrameController()
{
	if (PrevFrameBtn && NextFrameBtn && MonitorMode != PerFrame)
	{
		if (ControllerBar.IsValid())
		{
			ControllerBar->RemoveSlot(PrevFrameBtn.ToSharedRef());
			ControllerBar->RemoveSlot(NextFrameBtn.ToSharedRef());
			ControllerBar->RemoveSlot(CurFrameSpin.ToSharedRef());
			ControllerBar->RemoveSlot(TotalFrameText.ToSharedRef());
		}
	}
}

int32 SUnLuaMonitorPanel::OnGetMaxDepth() const
{
	return FUnLuaMonitor::GetInstance()->GetMaxDepth();
}

void SUnLuaMonitorPanel::OnMaxDepthChanged(int32 Depth)
{
	FUnLuaMonitor::GetInstance()->SetMaxDepth(Depth);
}

FText SUnLuaMonitorPanel::OnGetTotalFrameText() const
{
	return FText::FromString(FString::Printf(TEXT("/%d"), FUnLuaMonitor::GetInstance()->GetTotalFrames()));
}

int32 SUnLuaMonitorPanel::OnGetCurFrameIndex() const
{
	return FUnLuaMonitor::GetInstance()->GetCurFrameIndex();
}

void SUnLuaMonitorPanel::OnCurFrameIndexChanged(int32 Index)
{
	FUnLuaMonitor::GetInstance()->SetCurFrameIndex(Index);
}

void SUnLuaMonitorPanel::OnCloseTab(TSharedRef<SDockTab> Tab)
{
	TabIsOpening = false;
}

#undef LOCTEXT_NAMESPACE
