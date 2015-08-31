
#pragma once

#include "ITypeMeta.h"
#include "Sfinae.h"
#include "Singleton.h"

class IClassMeta : public virtual ITypeMeta
{
public:
    std::vector<IConstructorMeta*> constructors;
    std::vector<IFieldMeta*> fields;
    std::vector<IMethodMeta*> methods;
};

template <typename T>
class TypeMeta<T, IF(T, Class)> : public TypeMetaBase<T>, public IClassMeta, public Singleton<TypeMeta<T>>
{
public:
    Any CreateOnStack() override { throw std::exception(); }
    Any CreateOnHeap() override { throw std::exception(); }

    virtual ITypeMeta* PointeeTypeMeta() override
    {
        throw new std::exception();
    }
};
