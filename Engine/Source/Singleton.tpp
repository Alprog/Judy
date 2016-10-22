
#pragma once

#include <Singleton.h>

template <typename T, typename RealT>
T* Singleton<T, RealT>::getInstance()
{
    static RealT instance;
    return &instance;
}
