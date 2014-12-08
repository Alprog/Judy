
#include "App.h"
#include "Window.h"

#include <windows.h>
#include "iostream"

#include "Meta/Meta.h"
#include "Meta/Binder.h"

#include "Meta/ClassDefiner.h"
#include "Meta/TypeMeta.h"
#include "Meta/FieldMeta.h"

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

    auto a = serializer->Deserialize();


//    Type newObj = serializer->Deserialize<Type>();
//    lua_pop(L, 1);

//    serializer->Serialize(newObj);

    lua_getglobal(L, "Test");
    lua_insert(L, 1);
    lua_pcall(L, 1, LUA_MULTRET, 0);
}

int main(int argc, char *argv[])
{
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    Meta* meta = Meta::Instance();

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
