
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

    DeepPointer operator*()
    {
        return DeepPointer(*pointer, count - 1);
    }

    DeepPointer operator&() const
    {
        return DeepPointer(&pointer, count + 1);
    }

private:
    void** pointer;
    int count;
};
