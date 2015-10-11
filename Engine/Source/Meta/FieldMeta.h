
#pragma once

#include "IMemberMeta.h"
#include "Any.h"
#include "Serializer.h"
#include "Meta.h"

class Serializer;
class ITypeMeta;

class IFieldMeta : public IMemberMeta
{
public:
    virtual void set(Any& object, Any& value) = 0;
    virtual Any get(Any& object) = 0;
    virtual ITypeMeta* const GetType() = 0;
};

template <typename ClassType, typename FieldType>
class FieldMeta : public IFieldMeta
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

    virtual void set(Any& object, Any& value) override
    {
        object.as<ClassType*>()->*pointer = value.as<FieldType>();
    }

    virtual Any get(Any& object) override
    {
        return object.as<ClassType*>()->*pointer;
    }

    FieldType ClassType::*pointer;
};
