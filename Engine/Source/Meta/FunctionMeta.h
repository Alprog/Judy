
#pragma once

#include "ITypeMeta.h"
#include "Meta.h"
#include "Any.h"

class IFunctionMeta
{
public:
    std::string name;
    virtual ITypeMeta* GetReturnType() = 0;
    virtual size_t GetArgCount() = 0;
    virtual std::vector<ITypeMeta*> GetArgTypes() = 0;

    virtual Any Invoke(std::vector<Any>& args) = 0;

    template <typename... ArgTypes>
    inline Any Invoke(ArgTypes... args)
    {
        std::vector<Any> vector{args...};
        return Invoke(vector);
    }
};

template <typename ReturnType, typename... ArgTypes>
class FunctionMeta : public IFunctionMeta
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
class FunctionMeta<ReturnType> : public IFunctionMeta
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

template <size_t... I>
struct index_sequence {};

template <size_t N, size_t... I>
struct make_index_sequence : public make_index_sequence<N - 1, N - 1, I...> {};

template <size_t... I>
struct make_index_sequence<0, I...> : public index_sequence<I...>{};
