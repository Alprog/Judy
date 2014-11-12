
#pragma once

#include "vector"
#include "Variant.h"
#include "TypeMeta.h"
#include "MethodMeta.h"
#include "FunctionMeta.h"

class IConstructorMeta : public virtual IFunctionMeta
{
public:
    virtual void* Invoke(std::vector<Variant> args) = 0;
};

template <typename ClassType, typename... ArgTypes>
class ConstructorMeta : public IConstructorMeta, public FunctionMeta<ClassType*, ArgTypes...>
{
public:
    template <int... I>
    void* RealInvoke(std::vector<Variant> args, index_sequence<I...>)
    {
        return TypeMeta<ClassType>::New<ArgTypes...>(args[I]...);
    }

    virtual void* Invoke(std::vector<Variant> args) override
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

template <typename ClassType>
class ConstructorMeta<ClassType> : public IConstructorMeta, public FunctionMeta<ClassType*>
{
public:
    virtual void* Invoke(std::vector<Variant> args) override
    {
        if (args.size() == 0)
        {
            return TypeMeta<ClassType>::New();
        }
        else
        {
            throw new std::exception();
        }
    }
};

