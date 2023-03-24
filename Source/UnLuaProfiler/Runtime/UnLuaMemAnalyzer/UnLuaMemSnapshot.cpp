// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "UnLuaMemSnapshot.h"

FUnLuaMemSnapshot::FUnLuaMemSnapshot()
{

}

FUnLuaMemSnapshot::~FUnLuaMemSnapshot()
{

}

TSharedPtr<FUnLuaMemInfoNode> FUnLuaMemSnapshot::GetMemNode(const void* LuaObjAddress)
{
	if (LuaObjectMemNodeMap.Contains(LuaObjAddress))
	{
		return LuaObjectMemNodeMap[LuaObjAddress];
	}
	else
	{
		return nullptr;
	}
}

const void* FUnLuaMemSnapshot::Record(lua_State* L, const char* Desc, int32 Level, const void* Parent)
{
	const void* ObjAddress = lua_getaddr(L, -1);
	int32 Size = lua_sizeof(L, -1);
	const char* Type = lua_typename(L, lua_type(L, -1));

	TSharedPtr<FUnLuaMemInfoNode> pnode = GetMemNode(Parent);
	if (TSharedPtr<FUnLuaMemInfoNode> node = GetMemNode(ObjAddress))
	{
		if (node->parent != pnode)
		{
			node->count += 1;
		}
		//node->parent = pnode;
		node->desc = Desc;
		node->level = Level;
		node->parents.Add(Parent, pnode);
		lua_pop(L, 1);
		return nullptr;				// stop expanding tree
	}
	else
	{
		TSharedPtr<FUnLuaMemInfoNode> nnode = TSharedPtr<FUnLuaMemInfoNode>(new FUnLuaMemInfoNode());
		nnode->parent = pnode;
		nnode->desc = Desc;
		nnode->level = Level;
		nnode->size = Size;
		nnode->count = 1;
		nnode->address = ObjAddress;
		nnode->type = Type;
		if (pnode)
		{
			nnode->parents.Add(Parent, pnode);
			pnode->children.Add(nnode);
		}
		if (!Root)
		{
			Root = nnode;
		}
		LuaObjectMemNodeMap.Add(ObjAddress, nnode);
	}
	return ObjAddress;					// continue to expanding this object
}

int32 FUnLuaMemSnapshot::RecountNode(TSharedPtr<FUnLuaMemInfoNode> Node)
{
	int32 Size = 0;
	if (Node)
	{
		if (Node->state == White)
		{
			Size = Node->size;
		}
		for (int32 i = 0; i < Node->children.Num(); i++)
		{
			Size += RecountNode(Node->children[i]);
		}
	}
	Node->totalsize = Size;
	return Size;
}

void FUnLuaMemSnapshot::Dump()
{
	const FString Content = DumpNode(Root);
	const FString Path = FPaths::Combine(FPaths::ProjectContentDir(), TEXT("MemDump.txt"));
	FFileHelper::SaveStringToFile(Content, *Path, FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM);
}

FString FUnLuaMemSnapshot::DumpNode(TSharedPtr<FUnLuaMemInfoNode> Node)
{
	FString Content;
	if (Node)
	{
		if (Node->state == White)
		{
			for (int32 i = 0; i < Node->level; ++i)
			{
				Content.AppendChar(TEXT(' '));
			}
			Content.Append(FString::Printf(TEXT(" %s %s %p"), *Node->desc, *Node->type, Node->address));
			for (const TPair<const void*, TSharedPtr<FUnLuaMemInfoNode>> Entry : Node->parents)
			{
				Content.Append(FString::Printf(TEXT(" | %s %p |"), *Node->desc, Entry.Value->address));
			}
			Content.AppendChar(TEXT('\n'));
		}

		for (int32 i = 0; i < Node->children.Num(); i++)
		{
			Content += DumpNode(Node->children[i]);
		}
	}

	return Content;
}

//int32 FUnLuaMemSnapshot::GetTotalSize()
//{
//	int32 size = 0;
//	for (TPair<const void*, TSharedPtr<FUnLuaMemInfoNode>> Entry : LuaObjectMemNodeMap)
//	{
//		TSharedPtr<FUnLuaMemInfoNode> node = Entry.Value;
//		if (node)
//		{
//			size += node->size;
//		}
//	}
//	Root->size = size;
//	return size;
//}

int32 FUnLuaMemSnapshot::RecountSize()
{
	/* travel all nodes*/
	TotalSize = RecountNode(Root);
	return TotalSize;
}

void FUnLuaMemSnapshot::GenTimeStamp()
{
	SnapTimeStr = FDateTime::Now().ToString(TEXT("%H:%M:%S"));	// %H:%M:%S.%s
}

void FUnLuaMemSnapshot::RecordLinkedList(const TSharedPtr<FUnLuaMemSnapshot> Snapshot, const TSharedPtr<FUnLuaMemInfoNode> InNewnode)
{
	if (Snapshot->LuaObjectMemNodeMap.Contains(InNewnode->address))
	{
		TSharedPtr<FUnLuaMemInfoNode> wnode = Snapshot->LuaObjectMemNodeMap[InNewnode->address];
		wnode->state = White;
	}
	else
	{
		TSharedPtr<FUnLuaMemInfoNode> onode = InNewnode;	// origin node
		TSharedPtr<FUnLuaMemInfoNode> nnode = TSharedPtr<FUnLuaMemInfoNode>(new FUnLuaMemInfoNode(*onode));
		Snapshot->LuaObjectMemNodeMap.Add(nnode->address, nnode);
		while (nnode && onode->parent)
		{
			if (!Snapshot->LuaObjectMemNodeMap.Contains(onode->parent->address))
			{
				TSharedPtr<FUnLuaMemInfoNode> parent = TSharedPtr<FUnLuaMemInfoNode>(new FUnLuaMemInfoNode(*onode->parent));
				parent->state = Gray;
				parent->children.Add(nnode);
				nnode->parent = parent;
				nnode->parents.Add(parent->address, parent);
				nnode = parent;
				onode = onode->parent;
				Snapshot->LuaObjectMemNodeMap.Add(nnode->address, nnode);
			}
			else
			{
				TSharedPtr<FUnLuaMemInfoNode> parent = Snapshot->LuaObjectMemNodeMap[onode->parent->address];
				parent->children.Add(nnode);
				nnode->parent = parent;
				nnode->parents.Add(parent->address, parent);
				nnode = nullptr;
			}
		}
	}
}

TSharedPtr<FUnLuaMemSnapshot> FUnLuaMemSnapshot::LogicOperate(const FUnLuaMemSnapshot& Other, ESnapshotOp ESOP)
{
	switch (ESOP)
	{
	case SOP_AND:
		return *this & Other;
	case SOP_OR:
		return *this | Other;
	case SOP_XOR:
		return *this ^ Other;
	case SOP_None:
	default:
		return nullptr;
	}
}

TSharedPtr<FUnLuaMemSnapshot> FUnLuaMemSnapshot::operator&(const FUnLuaMemSnapshot& Other)
{
	TSharedPtr<FUnLuaMemSnapshot> Snapshot = TSharedPtr<FUnLuaMemSnapshot>(new FUnLuaMemSnapshot());
	Snapshot->Root = TSharedPtr<FUnLuaMemInfoNode>(new FUnLuaMemInfoNode(*Root));
	Snapshot->LuaObjectMemNodeMap.Add(Snapshot->Root->address, Snapshot->Root);
	for (TPair<const void*, TSharedPtr<FUnLuaMemInfoNode>> Iter : LuaObjectMemNodeMap)
	{
		if (Other.LuaObjectMemNodeMap.Contains(Iter.Key))
		{
			RecordLinkedList(Snapshot, Iter.Value);
		}
	}
	Snapshot->GenTimeStamp();
	Snapshot->RecountSize();
	return Snapshot;
}

TSharedPtr<FUnLuaMemSnapshot> FUnLuaMemSnapshot::operator|(const FUnLuaMemSnapshot& Other)
{
	TSharedPtr<FUnLuaMemSnapshot> Snapshot = TSharedPtr<FUnLuaMemSnapshot>(new FUnLuaMemSnapshot());
	Snapshot->Root = TSharedPtr<FUnLuaMemInfoNode>(new FUnLuaMemInfoNode(*Root));
	Snapshot->LuaObjectMemNodeMap.Add(Snapshot->Root->address, Snapshot->Root);
	for (TPair<const void*, TSharedPtr<FUnLuaMemInfoNode>> Iter : LuaObjectMemNodeMap)
	{
		RecordLinkedList(Snapshot, Iter.Value);
	}

	for (TPair<const void*, TSharedPtr<FUnLuaMemInfoNode>> Iter : Other.LuaObjectMemNodeMap)
	{
		if (!LuaObjectMemNodeMap.Contains(Iter.Key))
		{
			RecordLinkedList(Snapshot, Iter.Value);
		}
	}
	Snapshot->GenTimeStamp();
	Snapshot->RecountSize();
	return Snapshot;
}

TSharedPtr<FUnLuaMemSnapshot> FUnLuaMemSnapshot::operator^(const FUnLuaMemSnapshot& Other)
{
	TSharedPtr<FUnLuaMemSnapshot> Snapshot = TSharedPtr<FUnLuaMemSnapshot>(new FUnLuaMemSnapshot());
	Snapshot->Root = TSharedPtr<FUnLuaMemInfoNode>(new FUnLuaMemInfoNode(*Root));
	Snapshot->LuaObjectMemNodeMap.Add(Snapshot->Root->address, Snapshot->Root);
	for (TPair<const void*, TSharedPtr<FUnLuaMemInfoNode>> Iter : LuaObjectMemNodeMap)
	{
		if (!Other.LuaObjectMemNodeMap.Contains(Iter.Key))
		{
			RecordLinkedList(Snapshot, Iter.Value);
		}
	}

	for (TPair<const void*, TSharedPtr<FUnLuaMemInfoNode>> Iter : Other.LuaObjectMemNodeMap)
	{
		if (!LuaObjectMemNodeMap.Contains(Iter.Key))
		{
			RecordLinkedList(Snapshot, Iter.Value);
		}
	}
	Snapshot->GenTimeStamp();
	Snapshot->RecountSize();
	return Snapshot;
}
