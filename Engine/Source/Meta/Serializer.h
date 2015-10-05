
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
    Serializer();
    ~Serializer();

    std::string Serialize(Any object);

    template <typename Type>
    Type Deserialize(std::string text)
    {
        ITypeMeta* typeMeta = TypeMetaOf<Type>();
        return Deserialize(text, typeMeta);
    }

    Any Deserialize(std::string text, ITypeMeta* typeMeta = nullptr);

private:
    void Serialize(Any object, ITypeMeta* typeMeta);
    void SerializeAsClass(Any& object, ITypeMeta* type);
    void SerializeAsArray(Any& object, ITypeMeta* type);
    void SerializeAsMap(Any& object, ITypeMeta* type);

    Any DeserializeUnknown();
    Any DeserializeUnknownTable();
    Any DeserializeAsArray(IClassMeta* arrayMeta);
    Any DeserializeAsMap(IClassMeta* mapMeta);
    Any DeserializeAsClass(IClassMeta* classMeta);
    Any Deserialize(ITypeMeta* const typeMeta);

    lua_State* L;
};
