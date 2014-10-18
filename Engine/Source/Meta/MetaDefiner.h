
#pragma once

#include "Meta.h"
#include "TypeMeta.h"
#include "FieldMeta.h"
#include "MethodMeta.h"

template <typename ClassType>
class MetaDefiner
{
public:
    MetaDefiner(char* name)
    {
        TypeMeta* typeMeta = ClassMeta<ClassType>::Instance();
        typeMeta->name = name;
        Meta::Instance()->Types.push_back(typeMeta);
    }

    template <typename FieldType>
    MetaDefiner& field(char* name, FieldType ClassType::*pointer)
    {
        auto field = new ConcreteFieldMeta<ClassType, FieldType>(name, pointer);
        ClassMeta<ClassType>::Instance()->fields.push_back(field);
        return *this;
    }

    template <typename ReturnType, typename... ArgTypes>
    MetaDefiner& method(char* name, ReturnType(ClassType::*pointer)(ArgTypes...))
    {
        auto method = new ConcreteMethodMeta<ClassType, ReturnType, ArgTypes...>();
        method->name = name;
        method->pointer = pointer;
        ClassMeta<ClassType>::Instance()->methods.push_back(method);
        return *this;
    }
};

#include "MetaDefiner.tpp"
