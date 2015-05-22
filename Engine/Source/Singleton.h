
#pragma once

template <typename T>
class Singleton
{
public:
    static T* const Instance()
    {
        static T instance;
        return &instance;
    }
};
