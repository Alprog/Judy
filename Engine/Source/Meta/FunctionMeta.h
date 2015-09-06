
#pragma once

#include "ITypeMeta.h"
#include "Meta.h"

class IFunctionMeta
{
public:
    std::string name;
    virtual ITypeMeta* GetReturnType() = 0;
    virtual size_t GetArgCount() = 0;
    virtual std::vector<ITypeMeta*> GetArgTypes() = 0;

    virtual Any Invoke(std::vector<Any>& args) = 0;
};

template <typename ReturnType, typename... ArgTypes>
class FunctionMeta : virtual IFunctionMeta
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
class FunctionMeta<ReturnType> : virtual IFunctionMeta
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
