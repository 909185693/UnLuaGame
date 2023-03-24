// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "UnLuaTraceInfoTree.h"

enum EMonitorState : uint32
{
	CREATED =	0,
	STARTED =	1 << 0,
	INITED	=	1 << 1,
	RUNING	=	STARTED | INITED,
	PAUSE	=	1 << 2,
	//PAUSE =	1 << 3,
};

class UNLUAPROFILER_API FUnLuaMonitor
{
public:
	static FUnLuaMonitor* GetInstance()
	{
		static FUnLuaMonitor Instance;
		return &Instance;
	}

	void OnForward();

	void OnClear();

	void Tick(float DeltaTime);

	int32 GetMaxDepth() { return MaxDepth; }

	void SetMaxDepth(int32 Depth) { MaxDepth = Depth; }

	TSharedPtr<FUnLuaTraceInfoNode> GetRoot(uint32 FrameIndex = 0);

	bool IsRuning() { return State == RUNING; }

	void LoadFile(const FString& Path);

	void PrintToFile(const FString& Path);

	void SetMonitorMode(UnLuaMonitorMode Mode) { MonitorMode = Mode; }

	int32 GetTotalFrames() { return FramesTraceTreeList.Num(); }

	int32 GetCurFrameIndex() { return CurFrameIndex; }

	void SetCurFrameIndex(int32 Index);

	void SetSortMode(EMonitorSortMode Mode) { MonitorSortMode = Mode; }

	EMonitorSortMode GetSortMode() { return MonitorSortMode; }
private:
	FUnLuaMonitor();
	~FUnLuaMonitor();

	static void OnHook(lua_State* L, lua_Debug* ar);
	
    static void* LuaAllocator(void* ud, void* ptr, size_t osize, size_t nsize);

	void OnHookCall(lua_State* L, lua_Debug* ar);

	void OnHookReturn(lua_State* L, lua_Debug* ar);

	void OnHookReturn();

	void Init();

	void Start();

	void Stop();

	void Pause();

	void Resume();

	void PerFrameModeUpdate(bool Manual = false);

private:
	/* max depth of hook  tracking */
	uint32 MaxDepth = 100;

	/* current depth of hook tracking */
	uint32 CurDepth = 0;

	TSharedPtr<FUnLuaTraceInfoTree> CurTraceTree;

	TArray<TSharedPtr<FUnLuaTraceInfoTree>> FramesTraceTreeList;

	uint32 CurFrameIndex = 0;

	bool Started = false;

	bool Inited = false;

	bool ManualUpdated = false;

	uint32 State = CREATED;

	UnLuaMonitorMode MonitorMode = Total;

	EMonitorSortMode MonitorSortMode = EMonitorSortMode::TotalTime;

	static void* RunningCoroutine;
};
