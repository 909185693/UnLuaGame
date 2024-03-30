// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "UnLuaTraceInfoTree.h"

FUnLuaTraceInfoTree::FUnLuaTraceInfoTree()
{

}

FUnLuaTraceInfoTree::~FUnLuaTraceInfoTree()
{
	Root = nullptr;
	CurNode = nullptr;
}

void FUnLuaTraceInfoTree::Init()
{
	FString RootName("Root");
	Root = TSharedPtr<FUnLuaTraceInfoNode>(new FUnLuaTraceInfoNode(nullptr, RootName, TEXT("Root"), 0));
	CurNode = Root;
}

void FUnLuaTraceInfoTree::OnHookCall(lua_State* L, lua_Debug* ar, bool IsStatistics/* = false */)
{
	if (Root)
	{
		lua_getinfo(L, "nS", ar);
		TSharedPtr<FUnLuaTraceInfoNode> Child = GetChild(ar);
		if (Child->Parent == Root)
		{
			Root->FakeBeginInvoke();
		}
		Child->BeginInvoke();
		CurNode = Child;
		++CurDepth;
	}
}

void FUnLuaTraceInfoTree::OnHookReturn(lua_State* L, lua_Debug* ar, bool IsStatistics/* = false */)
{
	if (Root)
	{
		CurNode->EndInvoke();
		CurNode = CurNode->Parent;
		lua_getinfo(L, "nS", ar);
		--CurDepth;
		if (CurNode == Root)
		{
			Root->FakeEndInvoke();
		}
	}
}

void FUnLuaTraceInfoTree::OnHookReturn()
{
    if (Root && CurNode)
    {
        CurNode->EndInvoke();
        CurNode = CurNode->Parent;
        --CurDepth;
        if (CurNode == Root)
        {
            Root->FakeEndInvoke();
        }
    }
}

TSharedPtr <FUnLuaTraceInfoNode> FUnLuaTraceInfoTree::GetChild(lua_Debug* ar)
{
	TCHAR* Name = UTF8_TO_TCHAR(ar->name);
	FString ID = FString::Printf(TEXT("%s:%d~%d %s"), UTF8_TO_TCHAR(ar->short_src), ar->linedefined, ar->lastlinedefined, Name);
	TSharedPtr<FUnLuaTraceInfoNode> Child = CurNode->GetChild(ID);
	if (!Child)
	{
		Child = TSharedPtr<FUnLuaTraceInfoNode>(new FUnLuaTraceInfoNode(CurNode, ID, Name, ar->event));
		CurNode->AddChild(Child);
	}
	return Child;
}

void FUnLuaTraceInfoTree::CountSelfTime(EMonitorSortMode SortMode)
{
	if (CurNode != Root)
	{
		// 递归统计尚未返回的函数
		TSharedPtr<FUnLuaTraceInfoNode> Node = CurNode;
		while (Node)
		{
			Node->FakeEndInvoke();
			Node = Node->Parent;
		}
	}

	CountNodeSelfTime(Root, SortMode);
}

void FUnLuaTraceInfoTree::CountNodeSelfTime(TSharedPtr<FUnLuaTraceInfoNode> Node, EMonitorSortMode SortMode)
{
	if (Node.IsValid())
	{
		Node->Children.Sort([SortMode](const TSharedPtr<FUnLuaTraceInfoNode>& A, const TSharedPtr <FUnLuaTraceInfoNode>& B) {
			switch (SortMode)
			{
			case SelfTime:
				return A->SelfTime > B->SelfTime;
				break;
			case Average:
				return A->Average > B->Average;
				break;
			case Alloc:
				return A->AllocSize > B->AllocSize;
				break;
			case GC:
				return A->GCSize < B->GCSize;
				break;
			case Calls:
				return A->Count > B->Count;
				break;
			case TotalTime:
			default:
				return A->TotalTime > B->TotalTime;
				break;
			}
		});

		// ifdef CORRECT_TIME sub profiler's own time overhead
		//Node->SelfTime = Node->TotalTime - DEVIATION * Node->Count;
		//Node->Average = Node->Count > 0 ? Node->TotalTime / Node->Count : 0;
		//for (int32 i = 0; i < Node->Children.Num(); i++)
		//{
		//	Node->SelfTime -= Node->Children[i]->TotalTime;
		//	CountNodeSelfTime(Node->Children[i], SortMode);
		//}
		//return A->TotalTime > B->TotalTime;
	}
}

void FUnLuaTraceInfoTree::StatisticizeNode(TSharedPtr<FUnLuaTraceInfoNode> Node, TSharedPtr<FUnLuaTraceInfoNode> StatisticsNode)
{
	if (Node)
	{
		for (int32 i = 0; i < Node->Children.Num(); i++)
		{
			StatisticsNode->StatisticizeOtherNode(Node->Children[i]);
			StatisticizeNode(Node->Children[i], StatisticsNode);
		}
	}
}

TSharedPtr<FUnLuaTraceInfoNode> FUnLuaTraceInfoTree::Statisticize()
{
	TSharedPtr<FUnLuaTraceInfoNode> StatisticsNode = TSharedPtr<FUnLuaTraceInfoNode>(new FUnLuaTraceInfoNode(Root));
	StatisticizeNode(Root, StatisticsNode);
	return StatisticsNode;
}
