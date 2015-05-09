
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

std::unordered_map<std::type_index, ITpMt*> metas;

template <template<typename A> class T>
void FF(T<int> arg)
{
    printf("work\n");
}

template <typename T>
ITpMt* OL(T* p)
{
    auto index = std::type_index(typeid(*p));

    auto it = metas.find(index);

    if (it == metas.end())
    {

    }
    else
    {
        return it->second;
    }

    printf(typeid(*p).name());
    printf("\n");

    return nullptr;
}

template <typename T>
void BarDefiner()
{
    ClassDefiner<Bar<T>>()
        .field("a", &Bar<T>::a)
    ;
};

template <typename Type>
ITpMt* Get()
{
    ClassDefiner<Foo>("Foo")
        .field("foo_field", &Foo::foo_field)
    ;

    Type aa;
    std::string ss = typeid(aa).name();
    printf(ss.c_str());
    printf("\n");

    base_type<Type>::value a;

    std::string s = typeid(a).name();

    printf(s.c_str());
    printf("\n");
    fflush(stdout);

    return nullptr;
}

template <template <typename> class T1, typename T2>
ITpMt* YO(T1<T2> *t)
{

    printf("YO, MAN!");

    return nullptr;
}

class BBB
{
public:
    int a;
    int b;
};

template <>
class TypeMeta<BBB>
{
    TypeMeta()
    {
        printf("!!!!!");
    }
};

int main(int argc, char *argv[])
{

    //auto m = TypeMeta<BBB>::Instance();

    YO(new Bar<int>());

    Meta* meta = Meta::Instance();

    Foo* foo = new Foo();
    Foo* bar_int = new Bar<int>();
    Foo* bar_float = new Bar<float>();

    OL(foo);
    OL(bar_int);
    OL(bar_float);

    BarDefiner<int>();

    return 0;

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
