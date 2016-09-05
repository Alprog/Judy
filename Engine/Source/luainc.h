
#pragma once

extern "C"
{
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
}

bool lua_isemptytable(lua_State* L, int index);

#define lua_pushuserdata lua_pushuserdata_unsafe

