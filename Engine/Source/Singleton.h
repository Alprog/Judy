
#pragma once

#include "Meta/Sfinae.h"

template <typename T>
class Singleton
{
public:
    using SingletonType = Singleton<T>;

    inline static T* const Instance()
    {
        static T instance;
        return &instance;
    }
};

template <typename T>
class PlatformSingleton
{
public:
    using SingletonType = PlatformSingleton<T>;

    inline static T* const Instance();
};

template <typename T>
class TrivialSingleton
{
public:
    static T instance;

    inline static T* const Instance()
    {
        return &instance;
    }
};

template <typename T>
T TrivialSingleton<T>::instance;
