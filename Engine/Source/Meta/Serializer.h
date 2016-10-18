
#pragma once

#include "Any.h"
#include "ITypeMeta.h"
#include "Attributes.h"

struct lua_State;
class ITypeMeta;
class IClassMeta;

class Serializer
{
    template <typename> friend class List;
    template <typename, typename> friend class Map;
    template <typename> friend class Ref;

public:
    Serializer();
    ~Serializer();

    std::string serialize(Any object);

    template <typename Type>
    Type deserialize(std::string text)
    {
        ITypeMeta* typeMeta = typeMetaOf<Type>();
        return deserialize(text, typeMeta);
    }

    Any deserialize(std::string text, ITypeMeta* typeMeta = nullptr);

    inline lua_State* getL() const { return L; }

private:
    void serialize(Any object, ITypeMeta* typeMeta);
    void serializeAsClass(Any& object, IClassMeta* type);
    void serializeClassFields(Any& pointer, IClassMeta* classMeta);

    Any deserializeUnknown();
    Any deserializeUnknownTable();
    Any deserializeAsClass(IClassMeta* classMeta);
    void deserializeClassFields(Any& pointer, IClassMeta* classMeta);
    Any deserialize(ITypeMeta* const typeMeta);

    lua_State* L;
};
