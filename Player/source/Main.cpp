
#include "App.h"
#include "Window.h"

#ifdef WIN
#include <windows.h>
#endif

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
#include <io.h>

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
    meta->Init();

    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    //lua_getglobal(L, "_G");
    //lua_pushcfunction(L, 1, luaPrint);
    //lua_setfield(L, 1, "print");

    LuaBinder(L).Bind(meta);

    fflush(stdout);

    int descr = dup(fileno(stdout));

    int pipepines[2];
    _pipe(pipepines, 128 * 1024, 0);
    dup2(pipepines[1], fileno(stdout));

    for (int i = 0; i < 100; i++)
    {
        std::cout << "--------------";
        printf("HEYs");
    }
    fflush(stdout);
    dup2(descr, fileno(stdout));

    char buffer[1024 + 1];
    int result = 1024;
    do
    {
        result = read(pipepines[0], buffer, 1024);
        printf(buffer);
    }
    while (result == 1024);

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
