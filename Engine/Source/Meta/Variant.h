
#pragma once

class Variant
{
public:
    static const Variant empty;

    Variant(void)
        : size{ 0 }
        , data{ nullptr }
    {
    }

    template <typename Type>
    Variant(Type value)
    {
        data = new Type();
        *(Type*)data = value;
        size = sizeof(value);
    }

    template <typename Type>
    operator Type()
    {
        return *(Type*)data;
    }

    size_t size;
    void* data;
};
