
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
        Serialize(object, typeMeta);
    }

    Variant DeserializeUnknown();
    Variant DeserializeUnknownTable();

    Variant DeserializeAsClass(ITypeMeta* type);

    template <typename Type>
    Type Deserialize()
    {
        ITypeMeta* typeMeta = TypeMeta<Type>::Instance();
        return Deserialize(typeMeta);
    }

private:
    Variant Deserialize(ITypeMeta* const typeMeta);
    void Serialize(Variant object, ITypeMeta* const typeMeta);
};
