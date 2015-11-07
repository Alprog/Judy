
#pragma once

extern "C"
{
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
}

#define lua_pushuserdata lua_pushuserdata_unsafe

