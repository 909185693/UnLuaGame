// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

struct UNLUAPROFILER_API FUnLuaTraceInfoNode
{
	/* show name */
	FString Name = "anonymous";

	/* call time */
	double CallTime = 0;

	/* self time */
	double SelfTime = 0;

	/* total time */
	double TotalTime = 0;

	/* average time */
	double Average = 0;

    /* the allocated size of lua_State when this node invoke */
    float CallAllocSize = 0;

    /* the gced size of lua_State when this node return */
    float CallGCSize;

	/* the size of this node alloc */
	float AllocSize = 0;

	/* the size of this node release */
	float GCSize = 0;

	/* the num of calls */
	int32 Count = 0;

	/* debug info event 
	 * LUA_HOOKCALL
	 * LUA_HOOKRET 
	 * LUA_HOOKTAILCALL
	 * LUA_HOOKLINE
	 * LUA_HOOKCOUNT
	 */
	int32 Event = -1;

	/* node id */
	FString ID;

	/* parent node */
	TSharedPtr<FUnLuaTraceInfoNode> Parent = nullptr;

	/* all child nodes */
	TArray<TSharedPtr<FUnLuaTraceInfoNode>> Children;

	/* id map to FUnLuaTraceInfoNode */
	TMap<FString, TSharedPtr<FUnLuaTraceInfoNode>> ChildIDMap;
	
	FUnLuaTraceInfoNode(TSharedPtr<FUnLuaTraceInfoNode> InParent, FString& InID, const TCHAR* InName, int32 InEvent)
	{
		ID = InID;
		if (InName)
		{
			Name = InName;
		}
		Event = InEvent;
		Parent = InParent;
	}

	void AddChild(TSharedPtr<FUnLuaTraceInfoNode> Child)
	{
		Children.Add(Child);
		ChildIDMap.Add(Child->ID, Child);
	}

    // 只有Root才会调用
	void FakeBeginInvoke()
	{
		CallTime = GetTimeMs();
        CallAllocSize = UnLuaProfiler::AllocSize;
        CallGCSize = UnLuaProfiler::GCSize;
	}

    // 只有Root和一帧结束尚未返回的函数会调用
	void FakeEndInvoke()
	{
		double NowTime = GetTimeMs();
		TotalTime += NowTime - CallTime;
		CallTime = NowTime;

        AllocSize += (UnLuaProfiler::AllocSize - CallAllocSize) * 0.001f;
        GCSize += (UnLuaProfiler::GCSize - CallGCSize) * 0.001f;
	}

	void BeginInvoke()
	{
		CallTime = GetTimeMs();
        CallAllocSize = UnLuaProfiler::AllocSize;
        CallGCSize = UnLuaProfiler::GCSize;
		Count += 1;
	}

	int32 EndInvoke()
	{
		TotalTime += GetTimeMs() - CallTime;

        AllocSize += (UnLuaProfiler::AllocSize - CallAllocSize) * 0.001f;
        GCSize += (UnLuaProfiler::GCSize - CallGCSize) * 0.001f;
		return Event;
	}

	TSharedPtr<FUnLuaTraceInfoNode> GetChild(const FString& InID)
	{
		if (ChildIDMap.Contains(InID))
		{
			return ChildIDMap[InID];
		}
		return nullptr;
	}

	void Empty()
	{
		Name.Empty();
		CallTime = 0.f;
		SelfTime = 0.f;
		TotalTime = 0.f;
		Count = 0;
		Event = 0;
		ID.Empty();
		Parent = nullptr;
		Children.Empty();
		ChildIDMap.Empty();
	}

	FUnLuaTraceInfoNode(TSharedPtr<FUnLuaTraceInfoNode> Other)
	{
		ID = Other->ID;
		Name = Other->Name;
		CallTime = Other->CallTime;
		SelfTime = Other->SelfTime;
		TotalTime = Other->TotalTime;
		CallAllocSize = Other->CallAllocSize;
        CallGCSize = Other->CallGCSize;
		AllocSize = Other->AllocSize;
		GCSize = Other->GCSize;
		Count = Other->Count;
		Event = Other->Event;
		Parent = Other->Parent;
	}

	void StatisticizeOtherNode(TSharedPtr<FUnLuaTraceInfoNode> Other)
	{
		if (ChildIDMap.Contains(Other->ID))
		{
			TSharedPtr<FUnLuaTraceInfoNode> CNode = ChildIDMap[Other->ID];
			CNode->SelfTime += Other->SelfTime;
			CNode->TotalTime += Other->TotalTime;
			CNode->AllocSize += Other->AllocSize;
			CNode->GCSize += Other->GCSize;
			CNode->Count += Other->Count;
		}
		else
		{
			AddChild(TSharedPtr<FUnLuaTraceInfoNode>(new FUnLuaTraceInfoNode(Other)));
		}
		TotalTime += Other->TotalTime;
		AllocSize += Other->AllocSize;
		GCSize += Other->GCSize;
	}
};
