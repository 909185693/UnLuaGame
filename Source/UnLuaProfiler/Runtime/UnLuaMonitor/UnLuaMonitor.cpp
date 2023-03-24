// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "UnLuaMonitor.h"
#include "UnLuaProfilerBase.h"
#include "lstate.h"

void* FUnLuaMonitor::RunningCoroutine = nullptr;

FUnLuaMonitor::FUnLuaMonitor()
{
	CurTraceTree = TSharedPtr<FUnLuaTraceInfoTree>(new FUnLuaTraceInfoTree());
}

FUnLuaMonitor::~FUnLuaMonitor()
{
	CurTraceTree = nullptr;
}

void FUnLuaMonitor::Init()
{
	if (UnLua::GetState())
	{
		State |= INITED;
	}
	else
	{
		State &= (~INITED);
	}
	CurTraceTree->Init();
}

void FUnLuaMonitor::OnForward()
{
	if (State == RUNING)
	{
		Pause();
	}
	else if ((State & PAUSE) > 0)
	{
		Resume();
	}
	else
	{
		Start();
	}
}

void* FUnLuaMonitor::LuaAllocator(void* ud, void* ptr, size_t osize, size_t nsize)
{
    if (nsize == 0)
    {
        UnLuaProfiler::GCSize += osize;
        FMemory::Free(ptr);
        return nullptr;
    } 
    else
    {
        UnLuaProfiler::GCSize += osize;
        UnLuaProfiler::AllocSize += nsize;
        return FMemory::Realloc(ptr, nsize);
    }
}

void FUnLuaMonitor::Start()
{
	Init();
	if ((State & INITED) > 0)
	{
		if (lua_State* L = UnLua::GetState())
		{
			lua_sethook(L, OnHook, UnLuaProfiler::HookMask, 0);
			lua_setallocf(L, FUnLuaMonitor::LuaAllocator, nullptr);
		}
	}
	State |= STARTED;
}

void FUnLuaMonitor::Stop()
{
	if (State == RUNING)
	{
		if (lua_State* L = UnLua::GetState())
		{
			lua_sethook(L, nullptr, 0, 0);
		}
	}
	State &= (~STARTED);
}

void FUnLuaMonitor::Pause()
{
	if (State == RUNING)
	{
		if (lua_State* L = UnLua::GetState())
		{
			lua_sethook(L, nullptr, 0, 0);
		}
	}
	State |= PAUSE;
}

void FUnLuaMonitor::Resume()
{
	if ((State & PAUSE) > 0)
	{
		State &= (~PAUSE);
		if (lua_State* L = UnLua::GetState())
		{
			lua_sethook(L, OnHook, UnLuaProfiler::HookMask, 0);
		}
	}
}

void FUnLuaMonitor::OnClear()
{
	Stop();

	State = CREATED;

	FramesTraceTreeList.Empty();

	CurFrameIndex = 0;

	CurTraceTree = TSharedPtr<FUnLuaTraceInfoTree>(new FUnLuaTraceInfoTree());
}

/*static*/ void FUnLuaMonitor::OnHook(lua_State* L, lua_Debug* ar)
{
    int32 Event = ar->event;
	if (L == G(L)->mainthread)
	{
		if (nullptr != RunningCoroutine)
		{
			if (lua_State* CoroState = static_cast<lua_State*>(RunningCoroutine))
			{
				if (lua_status(CoroState) >= LUA_ERRRUN)
				{
					// Error on coroutine
					FUnLuaMonitor::GetInstance()->OnHookReturn();
				}
			}
			RunningCoroutine = nullptr;
		}
	}
	else
	{
		// may be running a coroutine
		RunningCoroutine = L;

		lua_getinfo(L, "nS", ar);
		if (nullptr != ar->name && strcmp(ar->name, "yield") == 0)
		{
			if (LUA_HOOKCALL == ar->event)
			{
				// Call corotinue yield regarded as a return
				Event = LUA_HOOKRET;
			}
			else if (LUA_HOOKRET == ar->event)
			{
				// Continue corotinue yield regarded as a function call
				Event = LUA_HOOKCALL;
			}
		}
	}
    
    switch (Event)
    {
    case LUA_HOOKCALL:
        FUnLuaMonitor::GetInstance()->OnHookCall(L, ar);
        break;
    case LUA_HOOKRET:
        FUnLuaMonitor::GetInstance()->OnHookReturn();
        break;
    default:
        break;
    }
}

void FUnLuaMonitor::OnHookCall(lua_State* L, lua_Debug* ar)
{
	if (CurTraceTree)
	{
		if (CurDepth < MaxDepth)
		{
			CurTraceTree->OnHookCall(L, ar, MonitorMode == Statistics);
		}
		CurDepth++;
	}
}

void FUnLuaMonitor::OnHookReturn(lua_State* L, lua_Debug* ar)
{
	if (CurTraceTree)
	{
		if (CurDepth <= MaxDepth)
		{
			CurTraceTree->OnHookReturn(L, ar, MonitorMode == Statistics);
		}
		CurDepth--;
	}
}

void FUnLuaMonitor::OnHookReturn()
{
	if (CurTraceTree)
	{
		if (CurDepth <= MaxDepth)
		{
			CurTraceTree->OnHookReturn();
		}
		CurDepth--;
	}
}

TSharedPtr<FUnLuaTraceInfoNode> FUnLuaMonitor::GetRoot(uint32 FrameIndex /* = 0 */)
{
	if ((State & INITED) > 0)
	{
		if (MonitorMode == PerFrame)
		{
			if (GetTotalFrames() > 0)
			{
				int32 Index = GetCurFrameIndex() < GetTotalFrames() ? CurFrameIndex - 1 : GetTotalFrames() - 1;
				return FramesTraceTreeList[Index]->GetRoot();
			}
			else
			{
				return nullptr;
			}
		}
		else if (MonitorMode == Statistics)
		{
			CurTraceTree->CountSelfTime(MonitorSortMode);
			return CurTraceTree->Statisticize();
		}
		else
		{
			CurTraceTree->CountSelfTime(MonitorSortMode);
			return CurTraceTree->GetRoot();
		}
	}
	return nullptr;
}

void FUnLuaMonitor::SetCurFrameIndex(int32 Index)
{
	if (Index > 0 && Index < GetTotalFrames())
	{
		CurFrameIndex = Index;
	}
	else
	{
		CurFrameIndex = GetTotalFrames();
	}
}

void FUnLuaMonitor::PerFrameModeUpdate(bool Manual /* = false */)
{
	if (FramesTraceTreeList.Num() > 0)
	{
		TSharedPtr<FUnLuaTraceInfoTree> PreFrameTree = FramesTraceTreeList[FramesTraceTreeList.Num() - 1];
		if (PreFrameTree->GetRoot() && PreFrameTree->GetRoot()->Children.Num() == 0)
		{
			FramesTraceTreeList.Pop();
			if (CurFrameIndex >= (uint32)FramesTraceTreeList.Num())
			{
				CurFrameIndex = FramesTraceTreeList.Num() - 1;
			}
		}
	}
	CurTraceTree->CountSelfTime(MonitorSortMode);
	FramesTraceTreeList.Add(CurTraceTree);
	CurTraceTree = TSharedPtr<FUnLuaTraceInfoTree>(new FUnLuaTraceInfoTree());
	CurTraceTree->Init();

	if (CurFrameIndex == FramesTraceTreeList.Num() - 1)
	{
		CurFrameIndex = FramesTraceTreeList.Num();
	}
}

void FUnLuaMonitor::Tick(float DeltaTime)
{
	if (State == RUNING)
	{
		// game stop
		if (!UnLua::GetState())
		{
			Stop();
		}

		if (MonitorMode == PerFrame && !ManualUpdated)
		{
			PerFrameModeUpdate();
		}
	}
	else if(State == STARTED)
	{
		// waiting game start
		if (UnLua::GetState())
		{
			OnForward();
		}
	}
}
