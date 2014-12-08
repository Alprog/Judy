
#pragma once

#include <vector>
#include <type_traits>

#include "ITypeMeta.h"
#include "Variant.h"

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

    virtual bool isVector() override
    {
        return false;
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
class TypeMeta<std::vector<Type>> : public TypeMeta<Type>
{
public:
    static TypeMeta<std::vector<Type>> instance;

    static TypeMeta* const Get()
    {
        return Instance();
    }

    static TypeMeta* const Instance()
    {
        return &instance;
    }

    virtual bool isVector() override
    {
        return true;
    }
};

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

    /*Variant CreateOnHeap() override
    {
        return new Type();
    }*/

    virtual Variant MakePointerTo(Variant& object) override
    {
        //Type* pointer = new Type();
        //*pointer = object.as<Type>();
        //return pointer;
        return Variant::empty;
    }
};

template <>
class TypeMeta<void> : public ITypeMeta
{
public:
    static TypeMeta<void> instance;

    static TypeMeta* const Get()
    {
        return Instance();
    }

    static TypeMeta* const Instance()
    {
        return &instance;
    }

    virtual bool isPointer() override { return false; }
    virtual bool isVector() override { return false; }
    virtual Variant CreateOnStack() override { return 0; }
    virtual Variant CreateOnHeap() override { return 0; }
    virtual ITypeMeta* DerefType() override { return 0; }
    virtual Variant Dereferencing(Variant& object) override { return 0; }
    virtual Variant MakePointerTo(Variant& object) override { return 0; }
};

template <typename Type>
TypeMeta<Type> TypeMeta<Type>::instance;

template <typename Type>
TypeMeta<Type*> TypeMeta<Type*>::instance;

template <typename Type>
TypeMeta<std::vector<Type>> TypeMeta<std::vector<Type>>::instance;
