
#pragma once

#include "Meta/Any.h"

template <typename T>
class DeepPointer
{
public:
    DeepPointer(void* pointer, int count)
        : pointer{pointer}
        , count{count}
    {
    }

    T* operator*()
    {
        if (count == 2)
        {
            return *static_cast<T**>(pointer);
        }
        else
        {
            auto p = static_cast<void**>(pointer);
            return *DeepPointer(*p, count - 1);
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
