
#include "App.h"
#include "Window.h"

#include <windows.h>
#include "iostream"

#include "tolua++.h"

TOLUA_API int tolua_Binding_open(lua_State* tolua_S);

extern "C"
{
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
}

int main(int argc, char *argv[])
{
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    tolua_Binding_open(L);

    if (luaL_loadfile(L, "Main.lua"))
    {
        std::cerr << "Something went wrong loading the chunk (syntax error?)" << std::endl;
        std::cerr << lua_tostring(L, -1) << std::endl;
        lua_pop(L, 1);
    }
    lua_pushnumber(L, 1.1);
    lua_setglobal(L, "cppvar");
    if (lua_pcall(L, 0, LUA_MULTRET, 0))
    {
      std::cerr << "Something went wrong during execution" << std::endl;
      std::cerr << lua_tostring(L, -1) << std::endl;
      lua_pop(L, 1);
    }

    lua_getglobal(L, "myluafunction");
    lua_pushnumber(L, 5);
    lua_pcall(L, 1, 1, 0);
    std::cout << "The return value of the function was " << lua_tostring(L, -1) << std::endl;
    lua_pop(L,1);


    lua_close(L);
}
