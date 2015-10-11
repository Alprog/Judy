
#pragma once

#include "Any.h"
#include "IPropertyMeta.h"

class ITypeMeta;

template <typename ClassType, typename FieldType>
class FieldMeta : public IPropertyMeta
{
public:
    virtual ITypeMeta* const GetType() override
    {
        return TypeMetaOf<FieldType>();
    }

    FieldMeta(std::string name, FieldType ClassType::*pointer)
    {
        this->name = name;
        this->pointer = pointer;
    }

    virtual void Set(Any& object, Any& value) override
    {
        object.as<ClassType*>()->*pointer = value.as<FieldType>();
    }

    virtual Any Get(Any& object) override
    {
        return object.as<ClassType*>()->*pointer;
    }

    FieldType ClassType::*pointer;
};
