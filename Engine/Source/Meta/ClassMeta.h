
#pragma once

#include "ITypeMeta.h"
#include "Sfinae.h"
#include "Singleton.h"

class ClassMetaBase : public ITypeMeta
{
public:
    bool isPointer() override { return false; }
    bool isVector() override { return false; }
    bool isClass() override { return true; }

    std::vector<IConstructorMeta*> constructors;
    std::vector<IFieldMeta*> fields;
    std::vector<IMethodMeta*> methods;
};

template <typename T>
class TypeMeta<T, IF(T, Class)> : public ClassMetaBase, public Singleton<TypeMeta<T>>
{
public:
    Any CreateOnStack() override { throw std::exception(); }
    Any CreateOnHeap() override { throw std::exception(); }

    virtual Any Dereferencing(Any& object) override
    {
        throw std::exception();
    }

    virtual Any MakePointerTo(Any& object) override
    {
        throw std::exception();
        //return &(object.as<T>());
    }

    virtual ITypeMeta* PointeeTypeMeta() override
    {
        throw new std::exception();
    }
};
