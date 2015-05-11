
#pragma once

#include "TypeMeta.h"
#include "Meta.h"

class IFunctionMeta
{
public:
    char* name;
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

    // GetReturnType

    template <typename Type>
    inline ITypeMeta* GetReturnTypeHelper()
    {
        return TypeMetaOf<ReturnType>();
    }

    template <>
    inline ITypeMeta* GetReturnTypeHelper<void>()
    {
        return nullptr;
    }

    ITypeMeta* GetReturnType() override
    {
        return GetReturnTypeHelper<ReturnType>();
    }

    // GetArgTypes

    template <int count>
    inline std::vector<ITypeMeta*> GetArgTypesHelper()
    {
        return { TypeMetaOf<ArgTypes>()... };
    }

    template <>
    inline std::vector<ITypeMeta*> GetArgTypesHelper<0>()
    {
        return {};
    }

    virtual std::vector<ITypeMeta*> GetArgTypes() override
    {
        return GetArgTypesHelper<sizeof...(ArgTypes)>();
    }
};

