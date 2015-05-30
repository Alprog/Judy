
#include "LuaMachine.h"

#include "Meta/Meta.h"
#include "Meta/Binder.h"

extern "C"
{
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
}

LuaMachine::LuaMachine()
{
}

LuaMachine::~LuaMachine()
{
}

void LuaMachine::Start(std::string scriptName)
{
    Stop();

    L = luaL_newstate();
    luaL_openlibs(L);
    LuaBinder(L).Bind(Meta::Instance());

    if (luaL_dofile(L, "Main.lua"))
    {
        //std::cerr << "Something went wrong loading the chunk (syntax error?)" << std::endl;
        //std::cerr << lua_tostring(L, -1) << std::endl;
        lua_pop(L, 1);
    }
}

void LuaMachine::Stop()
{
    if (L != nullptr)
    {
        lua_close(L);
        L = nullptr;
    }
}
