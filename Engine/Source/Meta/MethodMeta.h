
#pragma once

#include "Variant.h"
#include "TypeMeta.h"
#include <vector>

class MethodMeta
{
public:
    virtual Variant Invoke(void* object, std::vector<Variant> args) = 0;
    virtual std::vector<TypeMeta*> GetArgTypes() = 0;
    char* name;
};

template <size_t... I>
struct index_sequence {};

template <size_t N, size_t... I>
struct make_index_sequence : public make_index_sequence<N - 1, N - 1, I...> {};

template <size_t... I>
struct make_index_sequence<0, I...> : public index_sequence<I...>{};

template <typename ClassType, typename ReturnType, typename... ArgTypes>
class ConcreteMethodMetaBase : public MethodMeta
{
public:
    static const int ArgCount = sizeof...(ArgTypes);

    virtual std::vector<TypeMeta*> GetArgTypes() override
    {
        return{ ((TypeMeta*)ClassMeta<ArgTypes>::Instance())... };
    }

    template <int... I>
    ReturnType RealInvoke(void* object, std::vector<Variant> args, index_sequence<I...>)
    {
        return ((ClassType*)object->*pointer)(args.at(I)...);
    }

    ReturnType(ClassType::*pointer)(ArgTypes...);
};

template <typename ClassType, typename ReturnType, typename... ArgTypes>
class ConcreteMethodMeta : public ConcreteMethodMetaBase<ClassType, ReturnType, ArgTypes...>
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
class ConcreteMethodMeta<ClassType, void, ArgTypes...> : public ConcreteMethodMetaBase<ClassType, void, ArgTypes...>
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
};
