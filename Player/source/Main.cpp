
#include "App.h"
#include "Window.h"

#include <windows.h>
#include "iostream"

#include "Meta/Meta.h"

#include "tolua++.h"

#include "Meta/MetaDefiner.h"
#include "Meta/TypeMeta.h"
#include "Meta/FieldMeta.h"

TOLUA_API int tolua_Binding_open(lua_State* tolua_S);

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

    Type newObj = serializer->Deserialize<Type>();
    lua_pop(L, 1);

    serializer->Serialize(object);

    lua_getglobal(L, "Test");
    lua_insert(L, 1);
    lua_pcall(L, 1, LUA_MULTRET, 0);
}

int main(int argc, char *argv[])
{
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    tolua_Binding_open(L);

    Meta::Instance();

    if (luaL_dofile(L, "Main.lua"))
    {
        std::cerr << "Something went wrong loading the chunk (syntax error?)" << std::endl;
        std::cerr << lua_tostring(L, -1) << std::endl;
        lua_pop(L, 1);
    }

    TestStruct testStruct { 1, 2, "fff", { 4 } };
    SerialzeToTable(L, testStruct);

    lua_close(L);
}
