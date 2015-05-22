
#pragma once

#include "ITypeMeta.h"
#include "Sfinae.h"
#include "Singleton.h"

class PointerTypeMetaBase : public ITypeMeta
{
public:
    bool isPointer() override { return true; }
    bool isVector() override { return false; }
    bool isClass() override { return false; }
};

template <typename T>
class TypeMeta<T, typename enable_pointer<T>::type> : public PointerTypeMetaBase, public Singleton<TypeMeta<T>>
{
public:
    using pointeeType = typename std::remove_pointer<T>::type;

    Any CreateOnStack() override { return T(); }
    Any CreateOnHeap() override { throw new std::exception(); }

    virtual Any Dereferencing(Any& object) override
    {
        throw new std::exception();
        //return *(object.as<T*>());
    }

    virtual Any MakePointerTo(Any& object) override
    {
        throw new std::exception();
        //return &(object.as<T>());
    }

    virtual ITypeMeta* PointeeTypeMeta() override
    {
        return TypeMetaOf<pointeeType>();
    }
};
