
#pragma once

#include "Meta/Any.h"

template <typename T>
class DeepPointer
{
public:
    using pointeeType = T;

    DeepPointer()
        : pointer{nullptr}
        , count{2}
    {
    }

    DeepPointer(T** pointer)
        : pointer{pointer}
        , count{2}
    {
    }

    DeepPointer(void* pointer, int count)
        : pointer{pointer}
        , count{count}
    {
    }

    Any operator*()
    {
        if (count == 2)
        {
            return *static_cast<T**>(pointer);
        }
        else
        {
            return DeepPointer(*static_cast<void**>(pointer), count - 1);
        }
    }

    DeepPointer operator&()
    {
        return DeepPointer(&pointer, count + 1);
    }

private:
    void* pointer;
    int count;
};
