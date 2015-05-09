
#pragma once

template <typename T>
class Singleton
{
public:
    inline static T* const Instance()
    {
        return &instance;
    }

private:
    static T instance;
};

template <typename T>
T Singleton<T>::instance;
