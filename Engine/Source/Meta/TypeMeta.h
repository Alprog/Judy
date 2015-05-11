
#pragma once

#include <vector>
#include <type_traits>

#include "ITypeMeta.h"
#include "Any.h"
#include "Singleton.h"
#include "Sfinae.h"

template <typename T, typename Enable = void>
struct TypeMeta : public ITypeMeta
{
    virtual bool isPointer() override { return false; }
    virtual bool isVector() override { return false; }

    Any CreateOnStack() override
    {
        return T();
    }

    Any CreateOnHeap() override
    {
        return new T();
    }

    virtual Any Dereferencing(Any& object) override
    {
        return *object.as<T*>();
    }

    virtual Any MakePointerTo(Any& object) override
    {
        return &object.as<T>();
    }

    virtual ITypeMeta* DerefType() override
    {
        throw new std::exception();
    }

    template <typename... ArgTypes>
    inline static T* Constructor(ArgTypes... args)
    {
        return new T(args...);
    }
};

template <typename T>
struct TypeMeta<T, typename enable_pointer<T>::type> : public ITypeMeta
{
    virtual bool isPointer() override { return true; }
    virtual bool isVector() override { return false; }

    virtual ITypeMeta* DerefType() override
    {
        return Meta::Instance()->GetTypeMeta<T>();
    }

    Any CreateOnStack() override
    {
        return T();
    }

    Any CreateOnHeap() override
    {
        return new T();
    }

    virtual Any Dereferencing(Any& object) override
    {
        return *object.as<T*>();
    }

    virtual Any MakePointerTo(Any& object) override
    {
        return &object.as<T>();
    }
};

template <typename T>
struct IClassMeta : public ITypeMeta
{
};
