
#pragma once

#include <vector>
#include <type_traits>

#include "ITypeMeta.h"
#include "Any.h"
#include "Singleton.h"

template <typename Type, typename Enable = void>
class TypeMeta : public ITypeMeta, public Singleton<TypeMeta<Type>>
{
    static_assert(std::is_same<Enable, void>::value, "Enable type must be void");

public:
    virtual bool isPointer() override { return false; }
    virtual bool isVector() override { return false; }
    virtual bool isClass() override { return false; }

    Any CreateOnStack() override { return Type(); }
    Any CreateOnHeap() override { return new Type(); }

    virtual Any Dereferencing(Any& object) override
    {
        return std::exception();
        //return *(object.as<Type*>());
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

// Template Specializations:
#include "PointerTypeMeta.h"
#include "ClassMeta.h"

template <typename T>
inline ITypeMeta* TypeMetaOf()
{
    return TypeMeta<typename std::decay<T>::type>::Instance();
}

//template <typename T, typename enable_pointer<T>::type>
//inline ITypeMeta* TypeMetaOf()
//{
//    return nullptr;
//}

template <>
inline ITypeMeta* TypeMetaOf<void>()
{
    return nullptr;
}
