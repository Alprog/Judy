
#pragma once

#include <string>
#include "Any.h"
#include "Serializer.h"
#include "Meta.h"

class Serializer;
class ITypeMeta;

class IFieldMeta
{
public:
    virtual void set_local(Any& object, Any& value) = 0;
    virtual Any get_local(Any& object) = 0;

    virtual void set(Any& object, Any& value) = 0;
    virtual void* get(void* object) = 0;
    virtual ITypeMeta* const GetType() = 0;
    char* name;
};

template <typename ClassType, typename FieldType>
class FieldMeta : public IFieldMeta
{
public:
    virtual ITypeMeta* const GetType() override
    {
        return TypeMetaOf<FieldType>();
    }

    FieldMeta(char* name, FieldType ClassType::*pointer)
    {
        this->name = name;
        this->pointer = pointer;
    }

    virtual void set_local(Any& object, Any& value) override
    {
        object.as<ClassType>().*pointer = value.as<FieldType>();
    }

    virtual void set(Any& object, Any& value) override
    {
        //object.as<ClassType>().*pointer = value.as<FieldType>();

        (ClassType*)object->*pointer = value.as<FieldType>();
    }

    virtual Any get_local(Any& object) override
    {
        return object.as<ClassType>().*pointer;
    }

    virtual void* get(void* object) override
    {
        return &((ClassType*)object->*pointer);
    }

    FieldType ClassType::*pointer;
};
