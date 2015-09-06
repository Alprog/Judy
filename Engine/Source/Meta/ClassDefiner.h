
#pragma once

#include "Meta.h"
#include "TypeMeta.h"
#include "FieldMeta.h"
#include "MethodMeta.h"
#include "ConstructorMeta.h"

template <typename ClassType>
class ClassDefiner
{
public:
    IClassMeta* classMeta;

    ClassDefiner(Meta* meta, const char* name)
        : classMeta { TypeMeta<ClassType>::Instance() }
    {
        classMeta->name = name;

        auto type_index = std::type_index(typeid(ClassType));
        meta->typeMap.emplace(type_index, classMeta);
        meta->types.push_back(classMeta);
    }

    template <typename... ArgTypes>
    ClassDefiner& constructor()
    {
        auto constructor = new ConstructorMeta<ClassType, ArgTypes...>();
        classMeta->constructors.push_back(constructor);
        return *this;
    }

    template <typename FieldType>
    ClassDefiner& field(char* name, FieldType ClassType::*pointer)
    {
        auto field = new FieldMeta<ClassType, FieldType>(name, pointer);
        classMeta->fields[name] = field;
        return *this;
    }

    template <typename ReturnType, typename... ArgTypes>
    ClassDefiner& method(char* name, ReturnType(ClassType::*pointer)(ArgTypes...))
    {
        auto method = new MethodMeta<ClassType, ReturnType, ArgTypes...>();
        method->name = name;
        method->pointer = pointer;
        classMeta->methods[name] = method;
        return *this;
    }

    template <typename ReturnType, typename... ArgTypes>
    ClassDefiner& method(char* name, ReturnType(ClassType::*pointer)(ArgTypes...) const)
    {
        auto nonconstpointer = reinterpret_cast<ReturnType(ClassType::*)(ArgTypes...)>(pointer);
        return method(name, nonconstpointer);
    }

    template <typename T>
    ClassDefiner& valueType()
    {
        classMeta->valueType = TypeMetaOf<T>();
        return *this;
    }
};

#include "ClassDefiner.tpp"
