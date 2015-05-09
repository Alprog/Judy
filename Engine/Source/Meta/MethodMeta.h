
#pragma once

#include "Any.h"
#include "TypeMeta.h"
#include "FunctionMeta.h"
#include <vector>

class Node;

class IMethodMeta : public virtual IFunctionMeta
{
public:
    //virtual Any Invoke(void* object, std::vector<Variant> args) = 0;
};

template <size_t... I>
struct index_sequence {};

template <size_t N, size_t... I>
struct make_index_sequence : public make_index_sequence<N - 1, N - 1, I...> {};

template <size_t... I>
struct make_index_sequence<0, I...> : public index_sequence<I...>{};

template <typename ClassType, typename ReturnType, typename... ArgTypes>
class MethodMeta : public IMethodMeta, public FunctionMeta<ReturnType, ClassType*, ArgTypes...>
{
public:

    // Invoke

    template <int... I>
    inline ReturnType RealInvoke(void* object, std::vector<Any>& args, index_sequence<I...>)
    {
        std::vector<Any> vv = { args.at(I)... };
        return ((ClassType*)object->*pointer)(args.at(I)...);
    }

    template <typename type>
    inline Any InvokeHelper(void* object, std::vector<Any>& args)
    {
        return RealInvoke(object, args, make_index_sequence<sizeof...(ArgTypes)>());
    }

    template <>
    inline Any InvokeHelper<void>(void* object, std::vector<Any>& args)
    {
        RealInvoke(object, args, make_index_sequence<sizeof...(ArgTypes)>());
        return Any();
    }

    Any Invoke(std::vector<Any>& args) override
    {
        if (args.size() == sizeof...(ArgTypes) + 1)
        {
            void* object = args[0];
            args.erase(begin(args), begin(args) + 1);
            return InvokeHelper<ReturnType>(object, args);
        }
        else
        {
            throw new std::exception();
        }
    }

    ReturnType(ClassType::*pointer)(ArgTypes...);
};

/*template <typename ClassType, typename ReturnType, typename... ArgTypes>
class MethodMeta : public MethodMetaBase<ClassType, ReturnType, ArgTypes...>
{
public:
    Variant Invoke(void* object, std::vector<Variant> args) override
    {
        if (args.size() == sizeof...(ArgTypes))
        {
            return RealInvoke(object, args, make_index_sequence<sizeof...(ArgTypes)>());
        }
        else
        {
            throw new std::exception();
        }
    }
};

template <typename ClassType, typename... ArgTypes>
class MethodMeta<ClassType, void, ArgTypes...> : public MethodMetaBase<ClassType, void, ArgTypes...>
{
public:
    Variant Invoke(void* object, std::vector<Variant> args) override
    {
        if (args.size() == sizeof...(ArgTypes))
        {
            RealInvoke(object, args, make_index_sequence<sizeof...(ArgTypes)>());
            return Variant::empty;
        }
        else
        {
            throw new std::exception();
        }
    }
};*/
