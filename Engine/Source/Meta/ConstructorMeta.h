
#pragma once

#include "vector"
#include "Variant.h"
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
    inline Variant RealInvoke(std::vector<Variant>& args, index_sequence<I...>)
    {
        return TypeMeta<ClassType>::New<ArgTypes...>(args[I]...);
    }

    virtual Variant Invoke(std::vector<Variant>& args) override
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


