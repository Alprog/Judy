
#pragma once
#include <type_traits>

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

template <typename T, typename T2 = void>
struct enable_arithmetic : std::enable_if<std::is_arithmetic<T>::value, T2> {};

template <typename T, typename T2 = void>
struct enable_integral : std::enable_if<std::is_integral<T>::value, T2> {};

template <typename T, typename T2 = void>
struct enable_floating_point : std::enable_if<std::is_floating_point<T>::value, T2> {};

template <typename T, typename T2 = void>
struct enable_pointer : std::enable_if<std::is_pointer<T>::value, T2> {};

template <typename T, typename T2 = void>
struct enable_deep_pointer : std::enable_if<is_deep_pointer<T>::value, T2> {};

template <typename T, typename T2 = void>
struct enable_class : std::enable_if<std::is_class<T>::value, T2> {};

template <typename T, typename T2 = void>
struct enable_pure_class : std::enable_if<std::is_class<T>::value && !is_deep_pointer<T>::value, T2> {};

template<class T>
struct helper
{
    enum { RealPointer = std::is_pointer<T>::value };
    enum { DeepPointer = is_deep_pointer<T>::value };
    enum { Pointer = RealPointer || DeepPointer };

    enum { RealClass = std::is_class<T>::value };
    enum { Class = RealClass && !DeepPointer };

    enum { PointerToVoid = std::is_same<T, void*>::value };
    enum { PointerToAbstract = std::is_abstract<std::remove_pointer<T>>::value };
    enum { AllowDereferencing = (RealPointer && !PointerToAbstract && !PointerToVoid) || DeepPointer };
};

#define IF(T, C) typename std::enable_if<helper<T>::C>::type
#define IF_NOT(T, C) typename std::enable_if<!helper<T>::C>::type
