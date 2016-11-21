
#pragma once

#include <type_traits>

template <typename T>
struct fulldecay
{
    using type = typename std::decay<T>::type;
};

template <typename T>
struct fulldecay<T*>
{
    using type = typename std::decay<typename fulldecay<T>::type*>::type;
};

template <typename T> struct fulldecay<T&> : public fulldecay<T> {};
template <typename T> struct fulldecay<T&&> : public fulldecay<T> {};
template <typename T> struct fulldecay<T const> : public fulldecay<T> {};
