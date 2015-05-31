
#pragma once

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
