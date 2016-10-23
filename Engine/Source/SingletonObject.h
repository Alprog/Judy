
#pragma once

#include <Object.h>
#include <Singleton.h>

template <typename T, typename RealT = T>
class SingletonObject : public Object, public Singleton<T, RealT>
{
public:
    SingletonObject()
    {
        retain();
    }
};
