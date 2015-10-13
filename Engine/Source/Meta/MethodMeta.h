
#pragma once

#include "FunctionMeta.h"
#include <vector>
#include "Any.h"
#include "IndexSequence.h"

template <typename ClassType, typename ReturnType, typename... ArgTypes>
class MethodMeta : public FunctionMeta<ReturnType, ClassType*, ArgTypes...>
{
public:
    template <size_t... I>
    inline Any RealInvoke(void* object, SELECT_IF(ReturnType, Void, int, std::vector<Any>&) args, index_sequence<I...>)
    {
        return ((ClassType*)object->*pointer)(args.at(I)...);
    }

    template <size_t... I>
    inline Any RealInvoke(void* object, SELECT_IF(ReturnType, Void, std::vector<Any>&, int) args, index_sequence<I...>)
    {
        ((ClassType*)object->*pointer)(args.at(I)...);
        return Any::empty;
    }

    Any Invoke(std::vector<Any>& args) override
    {
        if (args.size() == sizeof...(ArgTypes) + 1)
        {
            void* object = args[0];
            args.erase(begin(args), begin(args) + 1);
            return RealInvoke(object, args, make_index_sequence<sizeof...(ArgTypes)>());
        }
        else
        {
            throw new std::exception();
        }
    }

    ReturnType(ClassType::*pointer)(ArgTypes...);
};
