
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
    virtual size_t GetArgCount() override
    {
        return sizeof...(ArgTypes);
    }

    ITypeMeta* GetReturnType() override
    {
        return TypeMetaOf<ReturnType>();
    }

    virtual std::vector<ITypeMeta*> GetArgTypes() override
    {
        return { TypeMetaOf<ArgTypes>()... };
    }
};

template <typename ReturnType>
class FunctionMeta<ReturnType> : public virtual IFunctionMeta
{
    virtual size_t GetArgCount() override
    {
        return 0;
    }

    ITypeMeta* GetReturnType() override
    {
        return TypeMetaOf<ReturnType>();
    }

    virtual std::vector<ITypeMeta*> GetArgTypes() override
    {
        return {};
    }
};
