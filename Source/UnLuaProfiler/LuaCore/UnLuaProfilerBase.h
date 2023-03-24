// Copyright 2022 CQUnreal. All Rights Reserved.

#pragma once

#include <chrono>
#include "CoreMinimal.h"
#include "CoreUObject.h"
#include "lua.hpp"

#if PLATFORM_WINDOWS
#define UNLUAPROFILER_PRINTF sprintf_s
#else
#define UNLUAPROFILER_PRINTF snprintf
#endif

typedef std::chrono::high_resolution_clock Clock;

int64 GetTimeNs() { return Clock::now().time_since_epoch().count(); }

double GetTimeMs() { return Clock::now().time_since_epoch().count() * 0.000001; }

int32 GetStateMemB();

float GetStateMemKb();

int32 lua_sizeof(lua_State* L, int32 idx);

const void* lua_getaddr(lua_State* L, int32 idx);

namespace UnLuaProfiler
{
	static const FName UnLuaMonitorTabName(TEXT("UnLuaMonitor"));

	static const FName UnLuaMemAnalyzerTabName(TEXT("UnLuaMemAnalyzer"));

	const int HookMask = LUA_MASKCALL | LUA_MASKRET;

	static uint32 AllocSize = 0;
	
	static uint32 GCSize = 0;
}

enum UnLuaMonitorMode : uint8
{
	PerFrame,		// Deep Copy TraceInfoTree PerFrame
	Total,			// Only one TraceInfoTree
	Statistics,		// Unfold TraceInfoTree
	MAX
};

enum EMonitorSortMode : uint8
{
	TotalTime,
	SelfTime,
	Average,
	Alloc,
	GC,
	Calls
};

enum ESnapshotOp : uint8
{
	SOP_None = 1 << 0,
	SOP_AND = 1 << 1,
	SOP_OR = 1 << 2,
	SOP_XOR = 1 << 3
};
