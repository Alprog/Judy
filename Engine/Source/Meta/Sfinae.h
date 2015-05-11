
#pragma once
#include <type_traits>

template <typename T>
struct enable_arithmetic : std::enable_if<std::is_arithmetic<T>::value> {};

template <typename T>
struct enable_integral : std::enable_if<std::is_integral<T>::value> {};

template <typename T>
struct enable_floating_point : std::enable_if<std::is_floating_point<T>::value> {};

template <typename T>
struct enable_pointer : std::enable_if<std::is_pointer<T>::value> {};

template <typename T>
struct enable_class : std::enable_if<std::is_class<T>::value> {};
