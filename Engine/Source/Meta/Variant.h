
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
        //printf("def constr\n");
    }

    template <typename T>
    Variant(T const& value)
    {
        size = sizeof(value);
        data = new char[size];
        //printf("templ const %i\n", data);
        memcpy(data, &value, size);
    }

    Variant(const Variant& v)
    {
        size = v.size;
        data = new char[size];
        //printf("copy constr* %i\n", data);
        memcpy(data, v.data, size);
    }

    ~Variant()
    {
        //printf("destroy %i\n", data);
        if (data != nullptr)
        {
            delete[] data;
        }
    }

    template <typename T>
    Variant& operator=(T const& value)
    {
        //printf("assign %i\n", data);
        if (data != nullptr)
        {
            delete[] data;
        }
        size = sizeof(value);
        data = new char[size];
        //printf("assign* %i\n", data);
        memcpy(data, &value, size);
    }

    template <typename Type>
    operator Type()
    {
        return *(Type*)data;
    }

    size_t size;
    void* data;
};
