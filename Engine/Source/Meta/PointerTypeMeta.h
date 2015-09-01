
#pragma once

#include "ITypeMeta.h"
#include "Sfinae.h"
#include "Singleton.h"
#include "Any.h"
#include "DeepPointer.h"

template <typename T>
class TypeMeta<T, typename enable_pointer<T>::type> : public TypeMetaBase<T>, public Singleton<TypeMeta<T>>
{
public:
    using pointeeType = typename std::remove_pointer<T>::type;

    virtual ITypeMeta* PointeeTypeMeta() override
    {
        return TypeMetaOf<pointeeType>();
    }
};

template <typename T>
class TypeMeta<T, typename enable_deep_pointer<T>::type> : public TypeMetaBase<T>, public Singleton<TypeMeta<T>>
{
public:
    virtual ITypeMeta* PointeeTypeMeta() override
    {
        return TypeMetaOf<typename T::pointeeType>();
    }
};
