
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
    ClassDefiner()
    {
        //ITypeMeta* typeMeta = TypeMeta<ClassType>::Instance();
        ITypeMeta* typeMeta = new TypeMeta<ClassType>();
        typeMeta->name = typeid(ClassType).name();
        typeMeta->isClass = true;

        auto type_index = std::type_index(typeid(ClassType));
        Meta::Instance()->typeMap.emplace(type_index, typeMeta);
        Meta::Instance()->types.push_back(typeMeta);
    }

    template <typename... ArgTypes>
    ClassDefiner& constructor()
    {
        auto constructor = new ConstructorMeta<ClassType, ArgTypes...>();
        Meta::Instance()->GetTypeMeta<ClassType>()->constructors.push_back(constructor);
        return *this;
    }

    template <typename FieldType>
    ClassDefiner& field(char* name, FieldType ClassType::*pointer)
    {
        auto field = new FieldMeta<ClassType, FieldType>(name, pointer);
        Meta::Instance()->GetTypeMeta<ClassType>()->fields.push_back(field);
        return *this;
    }

//    template <void* pointer>
//    ClassDefiner& method(char* name)
//    {
//        return *this;
//    }

    template <typename ReturnType, typename... ArgTypes>
    ClassDefiner& method(char* name, ReturnType(ClassType::*pointer)(ArgTypes...))
    {
        auto method = new MethodMeta<ClassType, ReturnType, ArgTypes...>();
        method->name = name;
        method->pointer = pointer;
        Meta::Instance()->GetTypeMeta<ClassType>()->methods.push_back(method);
        return *this;
    }

    template <typename ReturnType, typename... ArgTypes>
    ClassDefiner& method(char* name, ReturnType(ClassType::*pointer)(ArgTypes...) const)
    {
        auto nonconstpointer = reinterpret_cast<ReturnType(ClassType::*)(ArgTypes...)>(pointer);
        return method(name, nonconstpointer);
    }
};

#include "ClassDefiner.tpp"
