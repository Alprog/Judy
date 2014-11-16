
#pragma once

extern "C"
{
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
}

#include "Variant.h"
#include "FieldMeta.h"

#include "App.h"

class ITypeMeta;

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
        ITypeMeta* typeMeta = TypeMeta<Type>::Instance();
        Serialize(&object, typeMeta);
    }

    template <typename Type>
    Type Deserialize()
    {
        ITypeMeta* typeMeta = TypeMeta<Type>::Instance();

        Variant v = Deserialize(typeMeta);

        fflush(stdout);

        Type t = static_cast<Type>(v);

        fflush(stdout);

        return t;
    }

    template <>
    TestStruct Deserialize<TestStruct>()
    {
        ITypeMeta* typeMeta = TypeMeta<TestStruct>::Instance();

        Variant v = Deserialize(typeMeta);

        TestStruct* tt = static_cast<TestStruct*>(v);

        return *tt;
    }

private:
    Variant Deserialize(ITypeMeta* const typeMeta);
    void Serialize(void* object, ITypeMeta* const typeMeta);
};
