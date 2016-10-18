
#pragma once

#include "IMemberMeta.h"
#include "ITypeMeta.h"
#include "Meta.h"
#include "Any.h"
#include <unordered_set>
#include "IFunctionMeta.h"

template <typename ReturnType, typename... ArgTypes>
class FunctionMeta : public virtual IFunctionMeta
{
    virtual size_t getArgCount() override
    {
        return sizeof...(ArgTypes);
    }

    ITypeMeta* getReturnType() override
    {
        return typeMetaOf<ReturnType>();
    }

    virtual std::vector<ITypeMeta*> getArgTypes() override
    {
        return { typeMetaOf<ArgTypes>()... };
    }
};

template <typename ReturnType>
class FunctionMeta<ReturnType> : public virtual IFunctionMeta
{
    virtual size_t getArgCount() override
    {
        return 0;
    }

    ITypeMeta* getReturnType() override
    {
        return typeMetaOf<ReturnType>();
    }

    virtual std::vector<ITypeMeta*> getArgTypes() override
    {
        return {};
    }
};
