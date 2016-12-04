
#pragma once

template <typename T, typename RealT = T>
class [[Meta]] Singleton
{
public:
    using SingletonType = Singleton<T, RealT>;

    inline static T* getInstance();
};

template <typename T>
class Singleton<T, T>
{
public:
    using SingletonType = Singleton<T, T>;

    inline static T* getInstance()
    {
        static T instance;
        return &instance;
    }
};
