
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
    if (breakRequired || Breakpoints.IsSet(ar->source, ar->currentline))
    {
        auto level = 0;
        while (lua_getstack(L, level, ar))
        {
            lua_getinfo(L, "nSl", ar);

            printf("%s %s %i\n", ar->name, ar->source, ar->currentline);

            level++;
        }

        fflush(stdout);

        breakRequired = false;
        suspended = true;
        while (suspended)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(30));
        }
    }
}

void LuaMachine::Start(std::string scriptName, bool debug)
{
    isStarted = true;

    if (debug)
    {
        int mask = LUA_MASKLINE;
        lua_sethook(L, hook, mask, 0);
        breakRequired = true;
    }

    if (luaL_dofile(L, scriptName.c_str()))
    {
        isStarted = false;
        std::cerr << "Something went wrong loading the chunk (syntax error?)" << std::endl;
        std::cerr << lua_tostring(L, -1) << std::endl;
        lua_pop(L, 1);
    }
}

void LuaMachine::Break()
{
    breakRequired = true;
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
