
#pragma once

#include <vector>
#include <type_traits>

#include "ITypeMeta.h"
#include "Any.h"
#include "Singleton.h"
#include "Sfinae.h"
#include "BaseType.h"

template <typename Type, typename Enable = void>
class TypeMeta : public ITypeMeta
{
public:
    ITypeMeta* PointerType()
    {
        return Meta::Instance()->GetTypeMeta<Type*>();
    }

    virtual bool isPointer() override { return false; }
    virtual bool isVector() override { return false; }

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
        return *(object.as<Type*>());
    }

    virtual Any MakePointerTo(Any& object) override
    {
        return &(object.as<Type>());
    }

    virtual ITypeMeta* PointeeTypeMeta() override
    {
        throw new std::exception();
    }
};

class PointerTypeMetaBase : public ITypeMeta
{
    bool isPointer() override { return true; }
    bool isVector() override { return false; }
};

template <typename T>
class TypeMeta<T, typename enable_pointer<T>::type> : public PointerTypeMetaBase
{
public:
    typedef typename base_type<T>::value pointeeType;

    bool isPointer() override { return true; }

    Any CreateOnStack() override { return T(); }
    Any CreateOnHeap() override { return new T(); }

    virtual Any Dereferencing(Any& object) override
    {
        return *(object.as<T*>());
    }

    virtual Any MakePointerTo(Any& object) override
    {
        return &(object.as<T>());
    }

    virtual ITypeMeta* PointeeTypeMeta() override
    {
        return Meta::Instance()->GetTypeMeta<pointeeType>();
    }

};
