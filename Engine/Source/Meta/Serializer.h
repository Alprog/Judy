
#pragma once

extern "C"
{
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
}

#include "Any.h"
#include "ITypeMeta.h"

class ITypeMeta;

class Serializer
{
public:
    Serializer(lua_State* L);

    std::string Serialize(Any object);

    template <typename Type>
    Type Deserialize()
    {
        ITypeMeta* typeMeta = TypeMetaOf<Type>();
        return Deserialize(typeMeta);
    }

    Any Deserialize(std::string text);

private:
    void Serialize(Any object, ITypeMeta* typeMeta);

    Any DeserializeUnknown();
    Any DeserializeUnknownTable();
    Any DeserializeAsVector(IClassMeta* vectorMeta);
    Any DeserializeAsClass(IClassMeta* classMeta);
    Any Deserialize(ITypeMeta* const typeMeta);

    lua_State* L;
};
