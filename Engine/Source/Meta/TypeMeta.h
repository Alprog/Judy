
#pragma once

#include <vector>
#include <type_traits>
#include "Variant.h"

class IFieldMeta;
class IMethodMeta;
class IConstructorMeta;

class ITypeMeta
{
public:
    char* name;

    //void set(void* object, char* name, void* value);
    //void* get(void* object, char* name);
    //Variant invoke(void* object, char* name, std::vector<Variant> args);

    std::vector<IConstructorMeta*> constructors;
    std::vector<IFieldMeta*> fields;
    std::vector<IMethodMeta*> methods;

    virtual bool isPointer() = 0;
    virtual Variant DefaultConstructor() = 0;

    virtual Variant CreateOnStack() = 0;
    virtual Variant CreateOnHeap() = 0;

    template <typename Type>
    inline static ITypeMeta* const Get()
    {
        return TypeMeta<Type>::Get();
    }

    virtual ITypeMeta* DerefType() = 0;

    virtual Variant Dereferencing(Variant& object) = 0;
    virtual Variant MakePointerTo(Variant& object) = 0;
};

template <typename Type>
class TypeMeta : public ITypeMeta
{
public:
    static TypeMeta<Type> instance;

    static TypeMeta* const Get()
    {
        return Instance();
    }

    static TypeMeta* const Instance()
    {
        return &instance;
    }

    ITypeMeta* PointerType()
    {
        return TypeMeta<Type*>::Instance();
    }

    virtual bool isPointer() override
    {
        return false;
    }

    Variant DefaultConstructor() override
    {
        return new Type();
    }

    Variant CreateOnStack() override
    {
        return Type();
    }

    Variant CreateOnHeap() override
    {
        return new Type();
    }

    template <typename... Types>
    inline static Type* New(Types... args)
    {
        return new Type(args...);
    }

    virtual Variant Dereferencing(Variant& object) override
    {
        return *object.as<Type*>();
    }

    virtual Variant MakePointerTo(Variant& object) override
    {
        return Variant::empty;
    }

    virtual ITypeMeta* DerefType() override
    {
        throw new std::exception();
    }
};

//template <typename Type>
//class BuildInTypeMeta : TypeMeta<Type>
//{
//};

//template <typename Type>
//class ClassMeta : TypeMeta<Type>
//{
//};

//template <typename Type>
//class PointerTypeMeta : TypeMeta<Type>
//{
//};


template <typename Type>
class TypeMeta<Type*> : public TypeMeta<Type>
{
public:
    static TypeMeta<Type*> instance;

    static TypeMeta* const Get()
    {
        return Instance();
    }

    static TypeMeta* const Instance()
    {
        return &instance;
    }

    virtual bool isPointer() override
    {
        return true;
    }

    virtual ITypeMeta* DerefType() override
    {
        return TypeMeta<Type>::Instance();
    }

    Variant CreateOnHeap() override
    {
        return new Type();
    }
};


template <typename Type>
TypeMeta<Type> TypeMeta<Type>::instance;

template <typename Type>
TypeMeta<Type*> TypeMeta<Type*>::instance;

