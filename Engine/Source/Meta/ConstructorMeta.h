
#pragma once

#include "vector"
#include "Variant.h"
#include "TypeMeta.h"
#include "MethodMeta.h"
#include "ConstructorMeta.h"

class IConstructorMeta
{
public:
    virtual size_t GetArgCount() = 0;
    virtual std::vector<ITypeMeta*> GetArgTypes() = 0;
    virtual void* Invoke(std::vector<Variant> args) = 0;
};

template <typename ClassType, typename... ArgTypes>
class ConstructorMeta : public IConstructorMeta
{
public:
    virtual size_t GetArgCount() override
    {
        return sizeof...(ArgTypes);
    }

    virtual std::vector<ITypeMeta*> GetArgTypes() override
    {
        return{ ((ITypeMeta*)TypeMeta<ArgTypes>::Instance())... };
    }

    template <int... I>
    void* RealInvoke(std::vector<Variant> args, index_sequence<I...>)
    {
        return TypeMeta<ClassType>::New<ArgTypes...>(args.at(I)...);
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
class ConstructorMeta<ClassType> : public IConstructorMeta
{
public:
    virtual size_t GetArgCount() override
    {
        return 0;
    }

    virtual std::vector<ITypeMeta*> GetArgTypes() override
    {
        return {};
    }

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

