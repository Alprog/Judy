
#pragma once
#include <type_traits>
#include "select_if.h"
#include <vector>
#include <unordered_set>

template <typename T>
class DeepPointer;

template <typename T>
struct is_deep_pointer
{
    static const bool value = false;
};

template <typename T>
struct is_deep_pointer<DeepPointer<T>>
{
    static const bool value = true;
};

template <typename T>
struct is_array
{
    static const bool value = false;
};

template <typename T>
struct is_array<std::vector<T>>
{
    static const bool value = true;
};

template <typename T>
struct is_array<std::unordered_set<T>>
{
    static const bool value = true;
};

template<class T>
struct is
{
    enum { RealPointer = std::is_pointer<T>::value };
    enum { DeepPointer = is_deep_pointer<T>::value };
    enum { RealClass = std::is_class<T>::value };
    enum { Abstract = std::is_abstract<T>::value };
    enum { Array = is_array<T>::value };

    enum { Pointer = RealPointer || DeepPointer };
    enum { Class = RealClass && !DeepPointer };

    enum { ClassOrPointer = Class || Pointer };
    enum { AbstractClassOrRealPointer = Abstract || RealPointer };

    enum { Void = std::is_same<T, void>::value };
    enum { PointerToVoid = std::is_same<T, void*>::value };
    enum { PointerToAbstract = std::is_abstract<typename std::remove_pointer<T>::type>::value };
    enum { AllowDereferencing = (RealPointer && !PointerToAbstract && !PointerToVoid) || DeepPointer };
};

#define IF(T, C) typename std::enable_if<is<T>::C>::type
#define IF_NOT(T, C) typename std::enable_if<!is<T>::C>::type

#define SELECT_IF(T, C, T1, T2) typename select_if<is<T>::C, T1, T2>::type
