
#pragma once

#include "memory.h"
#include "stdio.h"

class Variant
{
public:
    static const Variant empty;

    Variant(void)
        : size{ 0 }
        , data{ nullptr }
    {
    }

    template <typename T>
    Variant(T const& value)
    {
        size = sizeof(value);
        data = new char[size];
        memcpy(data, &value, size);
    }

    Variant(const Variant& v)
    {
        size = v.size;
        data = new char[size];
        memcpy(data, v.data, size);
    }

    ~Variant()
    {
        if (data != nullptr)
        {
            delete[] data;
        }
    }

    template <typename T>
    Variant& operator=(T const& value)
    {
        if (data != nullptr)
        {
            delete[] data;
        }
        size = sizeof(value);
        data = new char[size];
        memcpy(data, &value, size);
        return *(this);
    }

    template <typename Type>
    inline Type as()
    {
        return *(Type*)data;
    }

    template <typename Type>
    operator Type()
    {
        return *(Type*)data;
    }

    size_t size;
    void* data;
};
