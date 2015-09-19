
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

int const maxStackSize = 256;

LuaMachine::LuaMachine()
    : L{nullptr}
    , isStarted{false}
    , breakCallback{nullptr}
    , resumeCallback{nullptr}
    , level{0}
    , breakRequiredLevel{0}
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
    LuaMachine::Instance()->Hook(ar);
}

void LuaMachine::Hook(lua_Debug *ar)
{
    if (ar->event == LUA_HOOKCALL)
    {
        level++;
    }
    else if (ar->event == LUA_HOOKRET)
    {
        level--;
    }
    else
    {
        if (level <= breakRequiredLevel)
        {
            Break(ar);
        }
        else
        {
            lua_getinfo(L, "S", ar);
            if (breakpoints.IsSet(ar->source, ar->currentline))
            {
                Break(ar);
            }
        }
    }
}

void LuaMachine::Break(lua_Debug *ar)
{
    breakRequiredLevel = 0;

    stack.calls.clear();

    auto index = 0;
    while (lua_getstack(L, index, ar))
    {
        lua_getinfo(L, "nSl", ar);
        stack.calls.push_back(GetCallInfo(ar));
        index++;
    }

    if (breakCallback) breakCallback();

    SuspendExecution();

    if (resumeCallback) resumeCallback();
}

CallInfo LuaMachine::GetCallInfo(lua_Debug *ar)
{
    auto name = ar->name ? ar->name : "";
    auto source = ar->source ? ar->source : "";
    auto line = ar->currentline;
    auto startLine = ar->linedefined;
    auto endLine = ar->lastlinedefined;
    return CallInfo(name, source, line, startLine, endLine);
}

void LuaMachine::SuspendExecution()
{
    suspended = true;
    while (suspended)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(30));
    }
}

void LuaMachine::Start(std::string scriptName, bool debug)
{
    isStarted = true;

    if (debug)
    {
        int mask = LUA_MASKCALL | LUA_MASKRET | LUA_MASKLINE;
        lua_sethook(L, hook, mask, 0);
        SuspendExecution();
    }

    if (luaL_dofile(L, scriptName.c_str()))
    {
        isStarted = false;
        std::cerr << "Something went wrong loading the chunk (syntax error?)" << std::endl;
        std::cerr << lua_tostring(L, -1) << std::endl;
        lua_pop(L, 1);
    }

    isStarted = false;
}

void LuaMachine::Pause()
{
    if (!suspended)
    {
        breakRequiredLevel = maxStackSize;
    }
}

void LuaMachine::Continue()
{
    if (suspended)
    {
        suspended = false;
    }
}

void LuaMachine::StepInto()
{
    if (suspended)
    {
        breakRequiredLevel = maxStackSize;
        suspended = false;
    }
}

void LuaMachine::StepOver()
{
    if (suspended)
    {
        breakRequiredLevel = level;
        suspended = false;
    }
}

void LuaMachine::StepOut()
{
    if (suspended)
    {
        breakRequiredLevel = level - 1;
        suspended = false;
    }
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
