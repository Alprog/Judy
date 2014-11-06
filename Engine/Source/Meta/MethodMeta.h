
#pragma once

#include "Variant.h"
#include "TypeMeta.h"
#include <vector>

class Node;

class IMethodMeta
{
public:
    virtual ITypeMeta* GetReturnType() = 0;
    virtual size_t GetArgCount() = 0;
    virtual std::vector<ITypeMeta*> GetArgTypes() = 0;

    virtual Variant Invoke(void* object, std::vector<Variant> args) = 0;

    char* name;
};

template <size_t... I>
struct index_sequence {};

template <size_t N, size_t... I>
struct make_index_sequence : public make_index_sequence<N - 1, N - 1, I...> {};

template <size_t... I>
struct make_index_sequence<0, I...> : public index_sequence<I...>{};

template <typename ClassType, typename ReturnType, typename... ArgTypes>
class MethodMeta : public IMethodMeta
{
public:

    virtual size_t GetArgCount() override
    {
        return sizeof...(ArgTypes);
    }

    // GetReturnType

    template <typename Type>
    inline ITypeMeta* GetReturnTypeHelper()
    {
        return TypeMeta<ReturnType>::Instance();
    }

    template <>
    inline ITypeMeta* GetReturnTypeHelper<void>()
    {
        return nullptr;
    }

    ITypeMeta* GetReturnType() override
    {
        return GetReturnTypeHelper<ReturnType>();
    }

    // GetArgTypes

    template <int count>
    inline std::vector<ITypeMeta*> GetArgTypesHelper()
    {
        return{ ((ITypeMeta*)TypeMeta<ArgTypes>::Instance())... };
    }

    template <>
    inline std::vector<ITypeMeta*> GetArgTypesHelper<0>()
    {
        return {};
    }

    virtual std::vector<ITypeMeta*> GetArgTypes() override
    {
        return GetArgTypesHelper<sizeof...(ArgTypes)>();
    }

    // Invoke

    template <int... I>
    inline ReturnType RealInvoke(void* object, std::vector<Variant> args, index_sequence<I...>)
    {
        return ((ClassType*)object->*pointer)(args.at(I)...);
    }

    template <typename type>
    inline Variant InvokeHelper(void* object, std::vector<Variant> args)
    {
        return RealInvoke(object, args, make_index_sequence<sizeof...(ArgTypes)>());
    }

    template <>
    inline Variant InvokeHelper<void>(void* object, std::vector<Variant> args)
    {
        RealInvoke(object, args, make_index_sequence<sizeof...(ArgTypes)>());
        return Variant::empty;
    }

    Variant Invoke(void* object, std::vector<Variant> args) override
    {
        if (args.size() == sizeof...(ArgTypes))
        {
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
