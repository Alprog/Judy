
#include "App.h"
#include "Window.h"

#include <windows.h>
#include "iostream"

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

class Serializer
{
public:
    lua_State* L;

    Serializer(lua_State* L)
    {
        this->L = L;
    }

    template <typename Type>
    void Serialize(Type object)
    {
        lua_createtable(L, 0, 0);
        TypeMeta* typeMeta = ClassMeta<Type>::Instance();
        for (auto fieldMeta : typeMeta->fields)
        {
            void* value = fieldMeta->get(&object);
            fieldMeta->Serialize(this, value);
            lua_setfield(L, -2, fieldMeta->name);
        }
    }

    template <typename Type>
    Type Deserialize()
    {
        Type type;

        TypeMeta* typeMeta = ClassMeta<Type>::Instance();
        for (auto fieldMeta : typeMeta->fields)
        {
            lua_getfield(L, -1, fieldMeta->name);
            Variant value = fieldMeta->Deserialize(this);
            fieldMeta->set(&type, value);
            lua_pop(L, 1);
        }

        return type;
    }

    //-------------------- SerializeField:

    template <typename Type>
    void SerializeField(void* value)
    {
        Serialize(*(Type*)value);
    }

    template <>
    void SerializeField<int>(void* value)
    {
        lua_pushnumber(L, *(int*)value);
    }

    template <>
    void SerializeField<char*>(void* value)
    {
        lua_pushstring(L, *(char**)value);
    }

    //-------------------- DeserializeField:

    template <typename Type>
    Variant DeserializeField()
    {
        return Deserialize<Type>();
    }

    template <>
    Variant DeserializeField<int>()
    {
        return lua_tointeger(L, -1);
    }

    template <>
    Variant DeserializeField<char*>()
    {
        return lua_tolstring(L, -1, nullptr);
    }
};

struct SubStruct
{
    int e;
};

struct TestStruct
{
    friend Serializer;

    int a;
    int b;
    char* c;
    SubStruct d;

public:
    TestStruct(int a, int b, char* c, SubStruct d)
    {
        this->a = a;
        this->b = b;
        this->c = c;
        this->d = d;
    }

private:
    TestStruct()
    {
    }
};


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
    MetaDefiner<SubStruct> def; def
            .field("e", &SubStruct::e);

    MetaDefiner<TestStruct> definer; definer
            .field("a", &TestStruct::a)
            .field("b", &TestStruct::b)
            .field("c", &TestStruct::c)
            .field("d", &TestStruct::d);

    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    tolua_Binding_open(L);

    if (luaL_dofile(L, "Main.lua"))
    {
        std::cerr << "Something went wrong loading the chunk (syntax error?)" << std::endl;
        std::cerr << lua_tostring(L, -1) << std::endl;
        lua_pop(L, 1);
    }

    TestStruct testStruct { 1, 2, "fff", { 4 } };
    SerialzeToTable(L, testStruct);

    /*lua_createtable(L, 0, 0);

    lua_pushnumber(L, 5);
    lua_setfield(L, 1, "k");

    lua_pushnumber(L, 1);
    lua_pushnumber(L, 6);
    lua_settable(L, 1);

    lua_pushnumber(L, 2);
    lua_pushnumber(L, 7);
    lua_settable(L, 1);

    lua_getglobal(L, "Test");
    lua_insert(L, 1);
    lua_pcall(L, 1, LUA_MULTRET, 0);*/

    /*lua_getglobal(L, "r");
    //lua_pushnumber(L, 5);
    lua_pcall(L, 0, LUA_MULTRET, 0);
    std::cout << "The return value of the function was " << lua_tostring(L, -1) << std::endl;
    lua_pop(L,1);

    lua_pushnumber(L, 1.1);
    lua_setglobal(L, "cppvar");
    if (lua_pcall(L, 0, LUA_MULTRET, 0))
    {
      std::cerr << "Something went wrong during execution" << std::endl;
      std::cerr << lua_tostring(L, -1) << std::endl;
      lua_pop(L, 1);
    }*/




    lua_close(L);
}
