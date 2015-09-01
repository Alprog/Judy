
#pragma once

#include "ITypeMeta.h"
#include "Sfinae.h"
#include "Singleton.h"

template <typename T>
class TypeMeta<T, IF(T, Class)> : public TypeMetaBase<T>, public Singleton<TypeMeta<T>>
{
public:
    Any CreateOnStack() override { throw std::exception(); }
    Any CreateOnHeap() override { throw std::exception(); }

    virtual ITypeMeta* PointeeTypeMeta() override
    {
        throw new std::exception();
    }
};
