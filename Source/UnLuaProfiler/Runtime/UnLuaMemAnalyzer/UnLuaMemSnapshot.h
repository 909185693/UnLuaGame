// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "UnLuaBase.h"
#include "UnLuaMemInfoNode.h"

class UNLUAPROFILER_API FUnLuaMemSnapshot
{
public:
	FUnLuaMemSnapshot();
	~FUnLuaMemSnapshot();

public:
	/* recount size of all the nodes */
	int32 RecountSize();

	/* get FUnLuaMemInfoNode by LuaObjAddress */
	TSharedPtr<FUnLuaMemInfoNode> GetMemNode(const void* LuaObjAddress);

	/* record the object at the top of luavm stack */
	const void* Record(lua_State* L, const char* Desc, int32 Level, const void* Parent);

	TSharedPtr<FUnLuaMemInfoNode> GetRoot() { return Root; }

	float GetTotalSizeMB() { return TotalSize / (1024.f * 1024.f); }

	/* %H:%M:%S */
	const FString GetSnapTimeStr() { return SnapTimeStr; }

	void GenTimeStamp();

	TSharedPtr<FUnLuaMemSnapshot> LogicOperate(const FUnLuaMemSnapshot& OtherSnapshoot, ESnapshotOp ESOP);
	//void Sort();

	void Dump();

private:
	/* accurately count the total size */
	//int32 GetTotalSize();

	/* count the node size */
	int32 RecountNode(TSharedPtr<FUnLuaMemInfoNode> Node);

	FString DumpNode(TSharedPtr<FUnLuaMemInfoNode> Node);

	TSharedPtr<FUnLuaMemSnapshot> operator&(const FUnLuaMemSnapshot& Other);

	TSharedPtr<FUnLuaMemSnapshot> operator|(const FUnLuaMemSnapshot& Other);

	TSharedPtr<FUnLuaMemSnapshot> operator^(const FUnLuaMemSnapshot& Other);

	void RecordLinkedList(const TSharedPtr<FUnLuaMemSnapshot> Snapshot, const TSharedPtr<FUnLuaMemInfoNode> InNewnode);

protected:
	TMap<const void*, TSharedPtr<FUnLuaMemInfoNode>> LuaObjectMemNodeMap;

private:
	TSharedPtr<FUnLuaMemInfoNode> Root = nullptr;

	/* byte */
	int32 TotalSize = 0;

	/* %H:%M:%S */
	FString SnapTimeStr;
};
