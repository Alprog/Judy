
#pragma once

#include "Any.h"
#include "ITypeMeta.h"

class lua_State;
class ITypeMeta;

class Serializer
{
    template <typename> friend class List;

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

    inline lua_State* getL() const { return L; }

private:
    void Serialize(Any object, ITypeMeta* typeMeta);
    void SerializeAsClass(Any& object, ITypeMeta* type);

    Any DeserializeUnknown();
    Any DeserializeUnknownTable();
    Any DeserializeAsClass(IClassMeta* classMeta);
    Any Deserialize(ITypeMeta* const typeMeta);

    lua_State* L;
};
