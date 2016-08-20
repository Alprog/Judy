
#pragma once

#include <Singleton.h>

template <typename T, typename RealT>
T* Singleton<T, RealT>::Instance()
{
    static RealT instance;
    return &instance;
}
