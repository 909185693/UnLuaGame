// Tencent is pleased to support the open source community by making UnLua available.
// 
// Copyright (C) 2019 THL A29 Limited, a Tencent company. All rights reserved.
//
// Licensed under the MIT License (the "License"); 
// you may not use this file except in compliance with the License. You may obtain a copy of the License at
//
// http://opensource.org/licenses/MIT
//
// Unless required by applicable law or agreed to in writing, 
// software distributed under the License is distributed on an "AS IS" BASIS, 
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 
// See the License for the specific language governing permissions and limitations under the License.

#include "UnLuaEx.h"
#include "LuaCore.h"
#include "Engine/DataTable.h"


namespace UnLua
{
	static int32 UDataTable_ToArray(lua_State* L)
	{
		int32 NumParams = lua_gettop(L);
		if (NumParams != 1)
		{
            return luaL_error(L, "invalid parameters!");
		}

		UDataTable* DataTable = Cast<UDataTable>(UnLua::GetUObject(L, 1));
		if (!DataTable)
		{
			return luaL_error(L, "invalid UDataTable");
		}

		UScriptStruct* StructType = DataTable->RowStruct;
		if (StructType == nullptr)
		{
			return luaL_error(L, "invalid RowStruct!");
		}

		auto& Env = UnLua::FLuaEnv::FindEnvChecked(L);
		TSharedPtr<UnLua::ITypeInterface> TypeInterface = Env.GetPropertyRegistry()->GetFieldProperty(StructType);
		if (!TypeInterface)
		{
			return luaL_error(L, "Failed to create TArray!");
		}

		FScriptArray* ScriptArray = new FScriptArray;

		void* Userdata = NewUserdataWithPadding(L, sizeof(FLuaArray), "TArray");
		FLuaArray* LuaArray = new(Userdata) FLuaArray(ScriptArray, TypeInterface, FLuaArray::OwnedBySelf);

		for (const TPair<FName, uint8*>& Pair : DataTable->GetRowMap())
		{
			LuaArray->Add(Pair.Value);
		}

		return 1;
	}

	static int32 UDataTable_ToMap(lua_State* L)
	{
		int32 NumParams = lua_gettop(L);
		if (NumParams != 1)
		{
			return luaL_error(L, "invalid parameters!");
		}

		UDataTable* DataTable = Cast<UDataTable>(UnLua::GetUObject(L, 1));
		if (!DataTable)
		{
			return luaL_error(L, "invalid UDataTable");
		}

		UScriptStruct* StructType = DataTable->RowStruct;
		if (StructType == nullptr)
		{
			return luaL_error(L, "invalid RowStruct!");
		}

		auto& Env = UnLua::FLuaEnv::FindEnvChecked(L);
		TSharedPtr<UnLua::ITypeInterface> ValueInterface = Env.GetPropertyRegistry()->GetFieldProperty(StructType);
		if (!ValueInterface)
		{
			return luaL_error(L, "Failed to create TMap!");
		}

		FScriptMap* ScriptMap = new FScriptMap;

		void* Userdata = NewUserdataWithPadding(L, sizeof(FLuaMap), "TMap");
		FLuaMap* LuaMap = new(Userdata) FLuaMap(ScriptMap, Env.GetPropertyRegistry()->GetNameProperty(), ValueInterface, FLuaMap::OwnedBySelf);

		void* ValueCache = (uint8*)LuaMap->ElementCache + LuaMap->MapLayout.ValueOffset;
		LuaMap->KeyInterface->Initialize(LuaMap->ElementCache);
		LuaMap->ValueInterface->Initialize(ValueCache);
		for (const TPair<FName, uint8*>& Pair : DataTable->GetRowMap())
		{
			LuaMap->KeyInterface->Copy(LuaMap->ElementCache, &Pair.Key);
			LuaMap->ValueInterface->Copy(ValueCache, Pair.Value);
			LuaMap->Add(LuaMap->ElementCache, ValueCache);
		}
		LuaMap->KeyInterface->Destruct(LuaMap->ElementCache);
		LuaMap->ValueInterface->Destruct(ValueCache);

		return 1;
	}

	static const luaL_Reg UDataTableLib[] =
	{
		{ "ToArray", UDataTable_ToArray },
		{ "ToMap", UDataTable_ToMap },
		{ nullptr, nullptr }
	};

	BEGIN_EXPORT_REFLECTED_CLASS(UDataTable)
        ADD_LIB(UDataTableLib)
	END_EXPORT_CLASS()
	IMPLEMENT_EXPORTED_CLASS(UDataTable)
}
