
#include "App.h"
#include "Window.h"

#include <windows.h>
#include "iostream"

#include "Meta/Meta.h"
#include "Meta/Binder.h"

#include "Meta/ClassDefiner.h"
#include "Meta/TypeMeta.h"
#include "Meta/FieldMeta.h"

#include "Meta/BaseType.h"

#include <typeindex>
#include <unordered_map>
#include <iostream>

extern "C"
{
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
}

template <typename Type>
void SerialzeToTable(lua_State* L, Type object)
{
    auto serializer = new Serializer(L);
    serializer->Serialize(object);

    auto a = serializer->DeserializeUnknown();
    lua_pop(L, 1);
    serializer->Serialize(a);

    lua_getglobal(L, "Test");
    lua_insert(L, 1);
    lua_pcall(L, 1, LUA_MULTRET, 0);
}

int main(int argc, char *argv[])
{
    Meta* meta = Meta::Instance();

    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    LuaBinder(L).Bind(meta);

    if (luaL_dofile(L, "Main.lua"))
    {
        std::cerr << "Something went wrong loading the chunk (syntax error?)" << std::endl;
        std::cerr << lua_tostring(L, -1) << std::endl;
        lua_pop(L, 1);
    }

    TestStruct testStruct { 1, 2, "fff", SubStruct() };
    SerialzeToTable(L, testStruct);

    lua_close(L);
}
