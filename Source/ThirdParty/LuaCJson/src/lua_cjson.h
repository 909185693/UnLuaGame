
#ifndef __LUA_CJSON_H_
#define __LUA_CJSON_H_

#include "lua.hpp"

#define USE_INTERNAL_FPCONV

extern int luaopen_cjson(lua_State *l);
extern int luaopen_cjson_safe(lua_State *l);

#endif // __LUA_CJSON_H_
