
#pragma once

template <typename T>
struct base_type
{
    typedef T value;
};

template <typename T>
struct base_type<T*> : base_type<T> {};

template <typename T>
struct base_type<T&> : base_type<T> {};

template <typename T>
struct base_type<T&&> : base_type<T> {};

template <typename T>
struct base_type<const T> : base_type<T> {};
