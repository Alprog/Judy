
#pragma once

#include "Meta.h"
#include "TypeMeta.h"
#include "FieldMeta.h"
#include "MethodMeta.h"
#include "ConstructorMeta.h"
#include "CFunctionMeta.h"
#include "PropertyMeta.h"

template <typename ClassType>
class ClassDefiner
{
public:
    IClassMeta* classMeta;
    IMemberMeta* lastMember;
    PropertyMeta* lastProperty;

    ClassDefiner(Meta* meta, const char* name)
        : classMeta{TypeMeta<ClassType>::Instance()}
        , lastMember{nullptr}
    {
        classMeta->name = name;

        auto type_index = std::type_index(typeid(ClassType));
        meta->typeMap.emplace(type_index, classMeta);
        meta->types.push_back(classMeta);
    }

    template <typename T>
    ClassDefiner& templateArgument()
    {
        classMeta->templateArguments.push_back(TypeMetaOf<T>());
        return *this;
    }

    template <typename T>
    ClassDefiner& base()
    {
        classMeta->baseTypes.push_back(TypeMetaOf<T>());
        return *this;
    }

    template <typename... ArgTypes>
    ClassDefiner& constructor()
    {
        auto constructor = new ConstructorMeta<ClassType, ArgTypes...>();
        classMeta->constructors.push_back(constructor);
        lastMember = constructor;
        return *this;
    }

    template <typename FieldType>
    ClassDefiner& field(std::string name, FieldType ClassType::*pointer)
    {
        auto field = new FieldMeta<ClassType, FieldType>(name, pointer);
        classMeta->fields[name] = field;
        lastMember = field;
        return *this;
    }

    template <typename ReturnType, typename... ArgTypes>
    ClassDefiner& method(std::string name, ReturnType(ClassType::*pointer)(ArgTypes...))
    {
        auto method = new MethodMeta<ClassType, ReturnType, ArgTypes...>();
        method->name = name;
        method->pointer = pointer;
        classMeta->methods[name] = method;
        lastMember = method;
        return *this;
    }

    template <typename ReturnType, typename... ArgTypes>
    ClassDefiner& method(std::string name, ReturnType(ClassType::*pointer)(ArgTypes...) const)
    {
        auto nonconstpointer = reinterpret_cast<ReturnType(ClassType::*)(ArgTypes...)>(pointer);
        return method(name, nonconstpointer);
    }

    template <typename ReturnType, typename... ArgTypes>
    ClassDefiner& function(std::string name, ReturnType(*pointer)(ArgTypes...))
    {
        auto function = new CFunctionMeta<ReturnType, ArgTypes...>();
        function->name = name;
        function->pointer = pointer;
        classMeta->functions[name] = function;
        lastMember = function;
        return *this;
    }

    ClassDefiner& property(std::string name)
    {
        auto property = new PropertyMeta(name);
        lastMember = property;
        lastProperty = property;
        return *this;
    }

    template <typename MethodType>
    inline ClassDefiner& getter(std::string name, MethodType pointer)
    {
        method(name, pointer);
        lastProperty->getter = static_cast<IFunctionMeta*>(lastMember);
        return *this;
    }

    template <typename MethodType>
    inline ClassDefiner& setter(std::string name, MethodType pointer)
    {
        method(name, pointer);
        lastProperty->setter = static_cast<IFunctionMeta*>(lastMember);
        return *this;
    }

    ClassDefiner& attr(std::string attributeName)
    {
        lastMember->attributes.insert(attributeName);
        return *this;
    }
};

#include "ClassDefiner.tpp"
