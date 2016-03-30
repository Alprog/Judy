
#pragma once

#include "Meta/Sfinae.h"

template <typename T>
class Singleton
{
public:
    inline static T* const Instance()
    {
        static T instance;
        return &instance;
    }
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
