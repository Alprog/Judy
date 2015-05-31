
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
    : L(nullptr)
    , executionThread(nullptr)
{
}

LuaMachine::~LuaMachine()
{
}

bool LuaMachine::IsStarted() const
{
    return L != nullptr;
}

void hook(lua_State *L, lua_Debug *ar)
{
    LuaMachine::Instance()->Hook(L, ar);
}

void LuaMachine::Hook(lua_State *L, lua_Debug *ar)
{
    lua_getinfo(L, "S", ar);
    printf("%s %i\n", ar->source, ar->currentline);

    /*for (int i = 0; i < 30; i++)
    {
        int a = lua_getstack(L, i, ar);
        if (a != 1) break;

        lua_getinfo(L, "Sn", ar);
        printf("%s %s %s %s\n", ar->source, ar->name, ar->namewhat, ar->what);

        //printf("%i %i\n", ar->event, ar->currentline);

    }*/

    breakpoint = true;
    while (breakpoint)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(30));
    }
}

void LuaMachine::Start(std::string scriptName)
{
    Stop();

    L = luaL_newstate();
    luaL_openlibs(L);
    LuaBinder(L).Bind(Meta::Instance());

    int mask = LUA_MASKLINE;
    lua_sethook(L, hook, mask, 0);

    executionThread = new std::thread(&LuaMachine::Execution, this, scriptName);
}

void LuaMachine::Execution(std::string scriptName)
{
    if (luaL_dofile(L, scriptName.c_str()))
    {
        std::cerr << "Something went wrong loading the chunk (syntax error?)" << std::endl;
        std::cerr << lua_tostring(L, -1) << std::endl;
        lua_pop(L, 1);
    }
}

void LuaMachine::Continue()
{
    breakpoint = false;
}

void LuaMachine::Stop()
{
    if (L != nullptr)
    {
        lua_close(L);
        L = nullptr;
    }
}
