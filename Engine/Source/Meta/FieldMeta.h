
#pragma once

#include <string>
#include "Variant.h"
#include "Serializer.h"

class TypeMeta;
class Serializer;

class FieldMeta
{
public:
    virtual void set(void* object, Variant value) = 0;

    virtual void set(void* object, void* value) = 0;
    virtual void* get(void* object) = 0;
    //virtual TypeMeta* GetType() = 0;
    char* name;

    virtual void Serialize(Serializer* serializer, void* value) = 0;
    virtual void* Deserialize(Serializer* serializer) = 0;
};

template <typename ClassType, typename FieldType>
class ConcreteFieldMeta : public FieldMeta
{
public:
    /*virtual TypeMeta* GetType() override
    {
        //return &(typeid(FieldType));
        //return (TypeMeta*)ConcreateTypeMeta<FieldType>::Instance();

        return (TypeMeta*)ClassMeta<FieldType>::Instance();
    }*/

    ConcreteFieldMeta(char* name, FieldType ClassType::*pointer)
    {
        this->name = name;
        this->pointer = pointer;
    }

    virtual void set(void* object, Variant value) override
    {
        (ClassType*)object->*pointer = value;
    }

    virtual void set(void* object, void* value) override
    {
        (ClassType*)object->*pointer = *(FieldType*)value;
    }

    virtual void* get(void* object) override
    {
        return &((ClassType*)object->*pointer);
    }

    virtual void Serialize(Serializer* serializer, void* value) override
    {
        serializer->SerializeField<FieldType>(value);
    }

    virtual void* Deserialize(Serializer* serializer) override
    {
        return serializer->DeserializeField<FieldType>();
    }

    FieldType ClassType::*pointer;
};