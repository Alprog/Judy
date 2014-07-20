
#include "App.h"
#include "Window.h"

#include <windows.h>
#include "iostream"

extern "C"
{
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"

}

int main(int argc, char *argv[])
{
    App* app = App::Instance();

    //auto renderer = new DX11Renderer();

    Window* window = Window::Create();

    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    if (luaL_loadfile(L, "luascript.lua"))
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



    lua_close(L);


    app->StartMainLoop();
}
