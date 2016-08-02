
#pragma once

#include "Singleton.h"
#include "Platforms.h"

template <typename T>
T* const PlatformSingleton<T>::Instance()
{
    static typename PlatformType<T>::type instance;
    return &instance;
}
