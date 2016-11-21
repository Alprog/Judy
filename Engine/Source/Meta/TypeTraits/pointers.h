
#pragma once

#include <cstddef>

template <typename T>
class Ref;

template <typename T>
class DeepPointer;

//--

template <typename T>
struct pointerOf
{
    using type = T*;
};

template <typename T>
struct pointerOf<T*>
{
    using type = DeepPointer<T>;
};

template <typename T>
struct pointerOf<Ref<T>>
{
    using type = DeepPointer<T>;
};

template <typename T>
struct pointerOf<DeepPointer<T>>
{
    using type = DeepPointer<T>;
};

//--

template <typename T>
struct pointeeOf
{
    using type = std::nullptr_t;
};

template <typename T>
struct pointeeOf<T*>
{
    using type = T;
};

template <typename T>
struct pointeeOf<Ref<T>>
{
    using type = typename Ref<T>::pointeeType;
};

template <typename T>
struct pointeeOf<DeepPointer<T>>
{
    using type = typename DeepPointer<T>::pointeeType;
};
