
#pragma once

#include "Meta/Sfinae.h"

template <typename T, typename RealT = T>
class Singleton
{
public:
    using SingletonType = Singleton<T, RealT>;

    inline static T* instance();
};

template <typename T>
class Singleton<T, T>
{
public:
    using SingletonType = Singleton<T, T>;

    inline static T* instance()
    {
        static T instance;
        return &instance;
    }
};
