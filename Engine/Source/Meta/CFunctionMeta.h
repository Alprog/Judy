
#pragma once

#include "Any.h"
#include "FunctionMeta.h"
#include <vector>

template <typename ReturnType, typename... ArgTypes>
class CFunctionMeta : public FunctionMeta<ReturnType, ArgTypes...>
{
public:
    template <int... I>
    inline ReturnType RealInvoke(std::vector<Any>& args, index_sequence<I...>)
    {
        return pointer(args.at(I)...);
    }

    Any Invoke(std::vector<Any>& args) override
    {
        if (args.size() == sizeof...(ArgTypes))
        {
            return RealInvoke(args, make_index_sequence<sizeof...(ArgTypes)>());
        }
        else
        {
            throw new std::exception();
        }
    }

    ReturnType(*pointer)(ArgTypes...);
};

template <typename... ArgTypes>
class CFunctionMeta<void, ArgTypes...> : public FunctionMeta<void, ArgTypes...>
{
public:
    template <size_t... I>
    inline Any RealInvoke(std::vector<Any>& args, index_sequence<I...>)
    {
        pointer(args.at(I)...);
        return Any::empty;
    }

    Any Invoke(std::vector<Any>& args) override
    {
        if (args.size() == sizeof...(ArgTypes))
        {
            return RealInvoke(args, make_index_sequence<sizeof...(ArgTypes)>());
        }
        else
        {
            throw new std::exception();
        }
    }

    void(*pointer)(ArgTypes...);
};
