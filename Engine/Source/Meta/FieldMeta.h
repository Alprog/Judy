
#pragma once

#include <string>
#include "Variant.h"
#include "Serializer.h"

class Serializer;
class ITypeMeta;

class IFieldMeta
{
public:
    virtual void set_local(Variant& object, Variant& value) = 0;
    virtual Variant get_local(Variant& object) = 0;

    virtual void set(Variant& object, Variant& value) = 0;
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
        return (ITypeMeta*)TypeMeta<FieldType>::Instance();
    }

    FieldMeta(char* name, FieldType ClassType::*pointer)
    {
        this->name = name;
        this->pointer = pointer;
    }

    virtual void set_local(Variant& object, Variant& value) override
    {
        object.as<ClassType>().*pointer = value.as<FieldType>();
    }

    virtual void set(Variant& object, Variant& value) override
    {
        //object.as<ClassType>().*pointer = value.as<FieldType>();

        (ClassType*)object->*pointer = value.as<FieldType>();
    }

    virtual Variant get_local(Variant& object) override
    {
        return object.as<ClassType>().*pointer;
    }

    virtual void* get(void* object) override
    {
        return &((ClassType*)object->*pointer);
    }

    FieldType ClassType::*pointer;
};
