// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "UnLuaMemInfoNode.h"
#include "UnLuaMemSnapshot.h"

class UNLUAPROFILER_API FUnLuaMemAnalyzer
{
public:
	FUnLuaMemAnalyzer();
	~FUnLuaMemAnalyzer();

public:
	static FUnLuaMemAnalyzer* GetInstance()
	{
		static FUnLuaMemAnalyzer Instance;
		return &Instance;
	}

	void Snapshot();

	void PopSnapshot();

	void ForceLuaGC();

	void OnSnapshotOperate(ESnapshotOp ESOP);

	void ShowSnapshot(int32 SnapshotIdx);

	void OnSelectSnapshot(int32 SnapshotIdx);

	void OnCancelOperate(int32 SnapshotIdx);

	bool OnDeleteSnapshot(int32 SnapshotIdx);

	TSharedPtr<FUnLuaMemSnapshot> GetShowingSnapshot() { return GetSnapshot(ShowingIndex); }

	TSharedPtr<FUnLuaMemInfoNode> GetShowingRoot() { return GetRoot(ShowingIndex); }

	TSharedPtr<FUnLuaMemSnapshot> GetSnapshot(int32 SnapshotIdx);

	int32 GetSnapshotNum() { return Snapshots.Num(); }

	void OnRefresh() { bNeedFreshSnapshotList = false; }

	bool NeedRefresh() { return bNeedFreshSnapshotList; }

	bool IsSelectedSnapshot(int32 SnapshotIdx) { return SnapshotIdx == OperateIndexLeft || SnapshotIdx == OperateIndexRight; }

	bool IsOperateMode(ESnapshotOp ESOP) { return ESOP == CurOperateMode; }

private:

	const char* key_tostring(lua_State* L, int index, char* buffer, const size_t bufsize);
	void update_node_desc(const void* p, const char* desc);

	/* create snapshot */
	TSharedPtr<FUnLuaMemSnapshot> CreateSnapshot();

	TSharedPtr<FUnLuaMemInfoNode> GetRoot(int32 Idx = -1);

	void TryOperateSnapshot();

	void traverse_lightuserdata(lua_State* L, const char* desc, int level, const void* parent);
	void traverse_string(lua_State* L, const char* desc, int level, const void* parent);
	void traverse_table(lua_State* L, const char* desc, int level, const void* parent);
	void traverse_userdata(lua_State* L, const char* desc, int level, const void* parent);
	void traverse_function(lua_State* L, const char* desc, int level, const void* parent);
	void traverse_thread(lua_State* L, const char* desc, int level, const void* parent);
	void traverse_object(lua_State* L, const char* desc, int level, const void* parent);

private:
	TSharedPtr<FUnLuaMemSnapshot> CurSnapshot;
	TArray<TSharedPtr<FUnLuaMemSnapshot>> Snapshots;

	int32 ShowingIndex = -1;

	int32 OperateIndexLeft = -1;

	int32 OperateIndexRight = -1;

	ESnapshotOp CurOperateMode = SOP_None;

	bool bNeedFreshSnapshotList = true;
};
