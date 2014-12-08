
#pragma once

#include "ITypeMeta.h"

struct IVariantData
{
    virtual ~IVariantData() {}

    virtual ITypeMeta* GetType() = 0;

    virtual IVariantData* copy() = 0;
};

template <typename T>
struct VariantData : public IVariantData
{
    T data;

    VariantData(T const& data)
        : data(data)
    {
    }

    virtual ITypeMeta* GetType() override
    {
        return ITypeMeta::Get<T>();
    }

    virtual IVariantData* copy() override
    {
        return new VariantData<T>(data);
    }
};
