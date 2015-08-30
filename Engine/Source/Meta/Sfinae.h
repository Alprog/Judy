
#pragma once
#include <type_traits>

template <typename T, typename T2 = void>
struct enable_arithmetic : std::enable_if<std::is_arithmetic<T>::value, T2> {};

template <typename T, typename T2 = void>
struct enable_integral : std::enable_if<std::is_integral<T>::value, T2> {};

template <typename T, typename T2 = void>
struct enable_floating_point : std::enable_if<std::is_floating_point<T>::value, T2> {};

template <typename T, typename T2 = void>
struct enable_pointer : std::enable_if<std::is_pointer<T>::value, T2> {};

template <typename T, typename T2 = void>
struct enable_class : std::enable_if<std::is_class<T>::value, T2> {};

#define IF(B, T) typename std::enable_if<B::value, T>::type

#define IF_POINTER(T1, T2) typename std::enable_if<std::is_pointer<T1>::value, T2>::type
