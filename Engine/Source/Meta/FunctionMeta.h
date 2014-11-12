
#pragma once

#include "TypeMeta.h"

class IFunctionMeta
{
public:
    char* name;
    virtual ITypeMeta* GetReturnType() = 0;
    virtual size_t GetArgCount() = 0;
    virtual std::vector<ITypeMeta*> GetArgTypes() = 0;

    virtual Variant Invoke(std::vector<Variant> args) = 0;
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
        return TypeMeta<ReturnType>::Instance();
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
        return{ ((ITypeMeta*)TypeMeta<ArgTypes>::Instance())... };
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

