
#pragma once

#include <vector>
#include <type_traits>

#include "ITypeMeta.h"
#include "Any.h"
#include "Singleton.h"

template <typename T, typename Enable = void>
class TypeMeta : public ITypeMeta, public Singleton<TypeMeta<T>>
{
    static_assert(std::is_same<Enable, void>::value, "Enable type must be void");

public:
    virtual bool isPointer() override { return false; }
    virtual bool isVector() override { return false; }
    virtual bool isClass() override { return false; }

    Any CreateOnStack() override { return T(); }
    Any CreateOnHeap() override { return new T(); }

    virtual Any Dereferencing(Any& object) override
    {
        return Deref<T>(object);
    }

    virtual Any MakePointerTo(Any& object) override
    {
        return MakePtr<T>(object);
    }

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
