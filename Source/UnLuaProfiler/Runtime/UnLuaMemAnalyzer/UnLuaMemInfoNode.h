// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

enum ENodeState : uint8
{
	White = 0,
	Gray = 1,
	Black = 2
};

struct UNLUAPROFILER_API FUnLuaMemInfoNode
{
	/* show name */
	FString name;

	/* detail description */
	FString desc;

	/* self size */
	int32 size;

	/* total size */
	int32 totalsize;

	/* the depth of this node */
	int32 level;

	/* the reference count of this lua object */
	int32 count;

	/* the type name of this lua object */
	FString type;

	/* the address of lua object */
	const void* address = nullptr;

	/*
	 * Node state used for FUnLuaMemSnapshot logical operations
	 * White:	Useful Node
	 * Gray:	The parent of White/Gray Node
	 * Black:	Useless Node
	 */
	ENodeState state = White;

	/* last recorded parent node */
	TSharedPtr<FUnLuaMemInfoNode> parent = nullptr;

	/* all child nodes */
	TArray<TSharedPtr<FUnLuaMemInfoNode>> children;

	/* all parent nodes. a node may be referenced by multi other nodes */
	TMap<const void*, TSharedPtr<FUnLuaMemInfoNode>> parents;

	FUnLuaMemInfoNode() { }

	FUnLuaMemInfoNode(const FUnLuaMemInfoNode& Copy)
	{
		name = Copy.name;
		desc = Copy.desc;
		size = Copy.size;
		level = Copy.level;
		count = Copy.count;
		type = Copy.type;
		address = Copy.address;
		parent = nullptr;
		children.Empty();
		parents.Empty();
	}

	void Empty()
	{
		name.Empty();
		desc.Empty();
		size = 0;
		level = 0;
		count = 0;
		type = 0;
		address = nullptr;
		parent = nullptr;
		children.Empty();
	}
};
