// Copyright 2022 CQUnreal. All Rights Reserved.

#pragma once

#include "UnLuaTraceInfoNode.h"

#define CORRECT_TIME false

#if CORRECT_TIME
#define DEVIATION 10	// default deviation 10ns
#else
#define DEVIATION 0
#endif // CORRECT_TIME


class UNLUAPROFILER_API FUnLuaTraceInfoTree
{
public:
	FUnLuaTraceInfoTree();
	~FUnLuaTraceInfoTree();

	void Init();

	void OnHookCall(lua_State* L, lua_Debug* ar, bool IsStatistics = false);

	void OnHookReturn(lua_State* L, lua_Debug* ar, bool IsStatistics = false);

	void OnHookReturn();

	bool IsOnRoot() { return CurNode == Root; }

	void CountSelfTime(EMonitorSortMode SortMode);

	TSharedPtr<FUnLuaTraceInfoNode> GetRoot() { return Root; }

	TSharedPtr<FUnLuaTraceInfoNode> Statisticize();

	void StatisticizeNode(TSharedPtr<FUnLuaTraceInfoNode> Node, TSharedPtr<FUnLuaTraceInfoNode> StatisticsNode);

private:
	TSharedPtr<FUnLuaTraceInfoNode> GetChild(lua_Debug* ar);

	void CountNodeSelfTime(TSharedPtr<FUnLuaTraceInfoNode> Node, EMonitorSortMode SortMode);

private:
	TSharedPtr<FUnLuaTraceInfoNode> Root;
	TSharedPtr<FUnLuaTraceInfoNode> CurNode;
	uint32 CurDepth = 0;
};