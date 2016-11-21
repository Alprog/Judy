
#pragma once

#include "IConstructorMeta.h"
#include "FunctionMeta.h"
#include "IndexSequence.h"
#include "Meta.h"

template <typename ClassType, typename... ArgTypes>
class ConstructorMeta : public IConstructorMeta, public FunctionMeta<ClassType, ArgTypes...>
{
public:

    template <size_t... I>
    static inline Any stackInvoke(std::vector<Any>& args, index_sequence<I...>)
    {
        return Meta::create<ClassType, ArgTypes...>( args.at(I)... );
    }

    template <size_t... I>
    static inline Any heapInvoke(std::vector<Any>& args, index_sequence<I...>)
    {
        return Meta::createNew<ClassType, ArgTypes...>( args.at(I)... );
    }

    virtual Any invoke(std::vector<Any>& args) override
    {
        if (args.size() == sizeof...(ArgTypes))
        {
            return stackInvoke(args, make_index_sequence<sizeof...(ArgTypes)>());
        }
        else
        {
            throw std::exception();
        }
    }

    virtual Any New(std::vector<Any>& args) override
    {
        if (args.size() == sizeof...(ArgTypes))
        {
            return heapInvoke(args, make_index_sequence<sizeof...(ArgTypes)>());
        }
        else
        {
            throw std::exception();
        }
    }

    virtual ITypeMeta* getNewType() override
    {
        return typeMetaOf<ClassType*>();
    }
};


