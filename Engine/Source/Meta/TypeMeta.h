
#pragma once

#include <vector>
#include <type_traits>

#include "ITypeMeta.h"
#include "Any.h"
#include "Singleton.h"

template <typename Type>
class TypeMeta : public ITypeMeta
{
public:
    ITypeMeta* PointerType()
    {
        return Meta::Instance()->GetTypeMeta<Type*>();
    }

    virtual bool isPointer() override
    {
        return false;
    }

    virtual bool isVector() override
    {
        return false;
    }

    Any CreateOnStack() override
    {
        return Type();
    }

    Any CreateOnHeap() override
    {
        return new Type();
    }

    template <typename... Types>
    inline static Type* New(Types... args)
    {
        return new Type(args...);
    }

    virtual Any Dereferencing(Any& object) override
    {
        return *object.as<Type*>();
    }

    virtual Any MakePointerTo(Any& object) override
    {
        return Any::empty;
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
    virtual bool isVector() override
    {
        return true;
    }
};

template <typename Type>
class TypeMeta<Type*> : public TypeMeta<Type>
{
public:
    virtual bool isPointer() override
    {
        return true;
    }

    virtual ITypeMeta* DerefType() override
    {
        return Meta::Instance()->GetTypeMeta<Type>();
    }

    /*Variant CreateOnHeap() override
    {
        return new Type();
    }*/

    virtual Any MakePointerTo(Any& object) override
    {
        //Type* pointer = new Type();
        //*pointer = object.as<Type>();
        //return pointer;
        return Any::empty;
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
    virtual Any CreateOnStack() override { return 0; }
    virtual Any CreateOnHeap() override { return 0; }
    virtual ITypeMeta* DerefType() override { return 0; }
    virtual Any Dereferencing(Any& object) override { return 0; }
    virtual Any MakePointerTo(Any& object) override { return 0; }
};
