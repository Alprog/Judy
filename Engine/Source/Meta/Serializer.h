
#pragma once

extern "C"
{
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
}

#include "Variant.h"
#include "FieldMeta.h"

class TypeMeta;

class Serializer
{
public:
    lua_State* L;

    Serializer(lua_State* L)
    {
        this->L = L;
    }

    void Serialize(void* object, TypeMeta* typeMeta);

    template <typename Type>
    void Serialize(Type object)
    {
        TypeMeta* typeMeta = ClassMeta<Type>::Instance();
        Serialize(&object, typeMeta);
    }

    Variant Deserialize(TypeMeta* typeMeta);

    template <typename Type>
    Type Deserialize()
    {
        TypeMeta* typeMeta = ClassMeta<Type>::Instance();
        return Deserialize(typeMeta);
    }
};
