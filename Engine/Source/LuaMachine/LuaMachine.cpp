
#include "LuaMachine.h"
#include <iostream>

#include "Meta/Meta.h"
#include "Meta/Binder.h"

extern "C"
{
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
}

LuaMachine::LuaMachine()
    : L{nullptr}
    , isStarted{false}
{
    L = luaL_newstate();
    luaL_openlibs(L);

    // search path for required scipts
    lua_getglobal(L, "package");
    lua_pushstring(L, "?.lua");
    lua_setfield(L, -2, "path");
    lua_pop(L, 1);
    LuaBinder(L).Bind(Meta::Instance());
}

LuaMachine::~LuaMachine()
{
    if (L != nullptr)
    {
        lua_close(L);
        L = nullptr;
    }
}

bool LuaMachine::IsStarted() const
{
    return isStarted;
}

bool LuaMachine::IsBreaked() const
{
    return isStarted && suspended;
}

void hook(lua_State *L, lua_Debug *ar)
{
    LuaMachine::Instance()->Hook(L, ar);
}

void LuaMachine::Hook(lua_State *L, lua_Debug *ar)
{
    lua_getinfo(L, "S", ar);
    if (Breakpoints.IsSet(ar->source, ar->currentline))
    {
        printf("%s %i\n", ar->source, ar->currentline);

        suspended = true;
        while (suspended)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(30));
        }
    }
}

void LuaMachine::EnableDebug()
{
    int mask = LUA_MASKLINE;
    lua_sethook(L, hook, mask, 0);
}

void LuaMachine::Start(std::string scriptName)
{
    isStarted = true;

    if (luaL_dofile(L, scriptName.c_str()))
    {
        isStarted = false;
        std::cerr << "Something went wrong loading the chunk (syntax error?)" << std::endl;
        std::cerr << lua_tostring(L, -1) << std::endl;
        lua_pop(L, 1);
    }

    printf("completed\n");
}

void LuaMachine::Continue()
{
    suspended = false;
}

void stopHook(lua_State *L, lua_Debug *ar)
{
    luaL_error(L, "Stop execution");
}

void LuaMachine::Stop()
{
    if (isStarted)
    {
        suspended = false;
        lua_sethook(L, stopHook, LUA_MASKCOUNT, 1);
    }
}
