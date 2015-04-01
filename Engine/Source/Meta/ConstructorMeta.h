
#pragma once

#include "vector"
#include "Any.h"
#include "TypeMeta.h"
#include "MethodMeta.h"
#include "FunctionMeta.h"

class IConstructorMeta : public virtual IFunctionMeta
{
public:
};

template <typename ClassType, typename... ArgTypes>
class ConstructorMeta : public IConstructorMeta, public FunctionMeta<ClassType, ArgTypes...>
{
public:
    template <int... I>
    inline Any RealInvoke(std::vector<Any>& args, index_sequence<I...>)
    {
        return TypeMeta<ClassType>::New<ArgTypes...>(args[I]...);
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


