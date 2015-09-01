
#pragma once

#include "vector"
#include "Any.h"
#include "FunctionMeta.h"
#include "MethodMeta.h"
#include "Meta.h"

class IConstructorMeta : public virtual IFunctionMeta
{
public:
};

class Node;

template <typename ClassType, typename... ArgTypes>
class ConstructorMeta : public IConstructorMeta, public FunctionMeta<ClassType, ArgTypes...>
{
public:

    template <size_t... I>
    inline Any RealInvoke(std::vector<Any>& args, index_sequence<I...>)
    {
        return Meta::Create<ClassType, ArgTypes...>( args.at(I)... );
        //return TypeMeta<ClassType>::New<ArgTypes...>( args.at(I)... );
    }

    virtual Any Invoke(std::vector<Any>& args) override
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
};


