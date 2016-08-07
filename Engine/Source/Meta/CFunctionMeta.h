
#pragma once

#include "FunctionMeta.h"
#include <vector>
#include "Any.h"
#include "IndexSequence.h"

template <typename ReturnType, typename... ArgTypes>
class CFunctionMeta : public FunctionMeta<ReturnType, ArgTypes...>
{
public:
    template <size_t... I>
    inline Any RealInvoke(SELECT_IF(ReturnType, Void, int, std::vector<Any>&) args, index_sequence<I...>)
    {
        return pointer(args.at(I)...);
    }

    template <size_t... I>
    inline Any RealInvoke(SELECT_IF(ReturnType, Void, std::vector<Any>&, int) args, index_sequence<I...>)
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

    ReturnType(*pointer)(ArgTypes...);
};
