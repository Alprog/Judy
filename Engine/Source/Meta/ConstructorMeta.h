
#pragma once

#include "vector"
#include "Any.h"
#include "FunctionMeta.h"
#include "Meta.h"

class IConstructorMeta : public virtual IFunctionMeta
{
public:
    virtual Any New(std::vector<Any>& args) = 0;
    virtual ITypeMeta* GetNewType() = 0;
};

template <typename ClassType, typename... ArgTypes>
class ConstructorMeta : public IConstructorMeta, public FunctionMeta<ClassType, ArgTypes...>
{
public:

    template <size_t... I>
    static inline Any StackInvoke(std::vector<Any>& args, index_sequence<I...>)
    {
        return Meta::Create<ClassType, ArgTypes...>( args.at(I)... );
    }

    template <size_t... I>
    static inline Any HeapInvoke(std::vector<Any>& args, index_sequence<I...>)
    {
        return Meta::CreateNew<ClassType, ArgTypes...>( args.at(I)... );
    }

    virtual Any Invoke(std::vector<Any>& args) override
    {
        if (args.size() == sizeof...(ArgTypes))
        {
            return StackInvoke(args, make_index_sequence<sizeof...(ArgTypes)>());
        }
        else
        {
            throw new std::exception();
        }
    }

    virtual Any New(std::vector<Any>& args) override
    {
        if (args.size() == sizeof...(ArgTypes))
        {
            return HeapInvoke(args, make_index_sequence<sizeof...(ArgTypes)>());
        }
        else
        {
            throw new std::exception();
        }
    }

    virtual ITypeMeta* GetNewType() override
    {
        return TypeMetaOf<ClassType*>();
    }
};


