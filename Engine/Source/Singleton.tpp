
#pragma once

#include <Singleton.h>

template <typename T, typename RealT>
T* Singleton<T, RealT>::instance()
{
    static RealT instance;
    return &instance;
}
