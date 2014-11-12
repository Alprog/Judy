
#pragma once

#include "Meta.h"
#include "TypeMeta.h"
#include "FieldMeta.h"
#include "MethodMeta.h"
#include "ConstructorMeta.h"

template <typename ClassType>
class MetaDefiner
{
public:
    MetaDefiner(char* name)
    {
        ITypeMeta* typeMeta = TypeMeta<ClassType>::Instance();
        typeMeta->name = name;
        printf("TYPE %p \n", typeMeta);
        Meta::Instance()->Types.push_back(typeMeta);
    }

    template <typename... ArgTypes>
    MetaDefiner& constructor()
    {
        auto constructor = new ConstructorMeta<ClassType, ArgTypes...>();
        TypeMeta<ClassType>::Instance()->constructors.push_back(constructor);
        return *this;
    }

    template <typename FieldType>
    MetaDefiner& field(char* name, FieldType ClassType::*pointer)
    {
        auto field = new FieldMeta<ClassType, FieldType>(name, pointer);
        TypeMeta<ClassType>::Instance()->fields.push_back(field);
        return *this;
    }

    template <void* pointer>
    MetaDefiner& method(char* name)
    {
        return *this;
    }

    template <typename ReturnType, typename... ArgTypes>
    MetaDefiner& method(char* name, ReturnType(ClassType::*pointer)(ArgTypes...))
    {
        auto method = new MethodMeta<ClassType, ReturnType, ArgTypes...>();
        method->name = name;
        method->pointer = pointer;
        TypeMeta<ClassType>::Instance()->methods.push_back(method);
        return *this;
    }
};

#include "MetaDefiner.tpp"
