
#pragma once

#include <string>
#include "Variant.h"
#include "Serializer.h"

class Serializer;
class ITypeMeta;

class IFieldMeta
{
public:
    virtual void set(Variant object, Variant value) = 0;
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

    virtual void set(Variant object, Variant value) override
    {
        (ClassType*)object->*pointer = value.as<FieldType>();
    }

    virtual void* get(void* object) override
    {
        return &((ClassType*)object->*pointer);
    }

    FieldType ClassType::*pointer;
};
