
#include "Lua.h"

bool lua_isemptytable(lua_State* L, int index)
{
    lua_pushnil(L);
    if (lua_next(L, index - 1))
    {
        lua_pop(L, 2);
        return false;
    }
    return true;
}
