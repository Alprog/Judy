
#pragma once

#include <vector>
#include <type_traits>

#include "ITypeMeta.h"
#include "Any.h"
#include "Singleton.h"

template <typename T>
class TypeMetaBase : public IClassMeta
{
public:
    virtual bool isPointer() override { return is<T>::Pointer; }
    virtual bool isClass() override { return is<T>::Class; }
    virtual bool isVector() override { return false; }

    virtual Any Dereferencing(Any& object) override
    {
        return Deref<T>(object);
    }

    virtual Any MakePointerTo(Any& object) override
    {
        return MakePtr<T>(object);
    }

private:
    template <typename T>
    static inline Any Deref(Any& object, IF(T, AllowDereferencing)* = nullptr)
    {
        return *(object.as<T>());
    }

    template <typename T>
    static inline Any Deref(Any& object, IF_NOT(T, AllowDereferencing)* = nullptr)
    {
        throw std::exception("invalid dereferencing");
    }

    template <typename T>
    inline Any MakePtr(Any& object, IF_NOT(T, AbstractClassOrRealPointer)* = nullptr)
    {
        return &object.as<T>();
    }

    template <typename T>
    static inline Any MakePtr(Any& object, IF(T, Abstract)* = nullptr)
    {
        throw std::exception("invalid referencing");
    }

    template <typename T>
    static inline Any MakePtr(Any& object, IF(T, RealPointer)* = nullptr)
    {
        return DeepPointer<std::remove_pointer<T>::type>(&object.as<T>());
    }
};


template <typename T, typename Enable = void>
class TypeMeta : public TypeMetaBase<T>, public Singleton<TypeMeta<T>>
{
    static_assert(std::is_same<Enable, void>::value, "Enable type must be void");

public:
    Any CreateOnStack() override { return T(); }
    Any CreateOnHeap() override { return new T(); }

    virtual ITypeMeta* PointeeTypeMeta() override
    {
        throw new std::exception();
    }
};

// Template Specializations:
#include "PointerTypeMeta.h"
#include "ClassMeta.h"

template <typename T>
inline ITypeMeta* TypeMetaOf()
{
    return TypeMeta<typename std::decay<T>::type>::Instance();
}

template <>
inline ITypeMeta* TypeMetaOf<void>()
{
    return nullptr;
}
