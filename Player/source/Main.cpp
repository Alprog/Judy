
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
#include "Meta/Sfinae.h"

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

class Foo
{
public:
    int foo_field;
    virtual void v() {}
};

template <typename T>
class Bar : public Foo
{
public:
    T a;
};

class ITpMt
{
    virtual bool isClass() { return false; }
};

class IClsMt : public ITpMt
{
    virtual bool isClass() override { return true; }
};

//----------------

template <typename Type>
class TpMt : public ITpMt
{

};

template <typename Type>
class TpMt<Type*> : public IClsMt
{
};

template <template<typename A> class T>
void FF(T<int> arg)
{
    printf("work\n");
}

//template <typename T>
//void BarDefiner()
//{
//    ClassDefiner<Bar<T>>()
//        .field("a", &Bar<T>::a)
//    ;
//};

//template <template <typename> class T1, typename T2>
//ITpMt* YO(T1<T2> *t)
//{

//    printf("YO, MAN!");

//    return nullptr;
//}

//template <typename T, typename Enable = void>
//class AA
//{
//    static_assert(std::is_same<Enable, void>::value, "Only one parameter");

//public:
//    void foo() { printf("0!\n"); }
//};

//template <class T>
//class AA<T, typename enable_integral<T>::type>
//{
//public:
//    void foo() { printf("1!\n"); }
//};

//template <class T>
//class AA<T, typename enable_pointer<T>::type>
//{
//public:
//    void foo() { printf("2!\n"); }
//};


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
