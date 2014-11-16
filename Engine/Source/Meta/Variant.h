
#pragma once

#include "memory.h"
#include "stdio.h"

struct IVariantData
{
    virtual ~IVariantData()
    {
    }

    virtual IVariantData* clone() = 0;
};

template <typename T>
struct VariantData : public IVariantData
{
    T data;

    VariantData(T const& data)
        : data(data)
    {
    }

    virtual IVariantData* clone() override
    {
        return new VariantData<T>(data);
    }
};

class Variant
{
public:
    static const Variant empty;

    IVariantData* p;

    Variant(void)
        : p {nullptr}
    {
    }

    template <typename T>
    Variant(T const& value)
    {
        p = new VariantData<T>(value);
    }

    // copy constructor
    Variant(const Variant& v)
    {
        if (v.p == nullptr)
        {
            p = nullptr;
        }
        else
        {
            p = v.p->clone();
        }
    }

    // move constructor
    Variant (Variant&& v)
    {
        p = v.p;
        v.p = nullptr;
    }

    ~Variant()
    {
        if (p != nullptr)
        {
            delete p;
        }
    }

    template <typename T>
    Variant& operator=(T const& value)
    {
        if (p != nullptr)
        {
            delete p;
        }
        p = new VariantData<T>(value);
        return *(this);
    }

    template <typename Type>
    inline Type as()
    {
        return ((VariantData<Type>*)p)->data;
    }

    template <typename Type>
    operator Type()
    {
        return ((VariantData<Type>*)p)->data;
    }
};

//class Variant
//{
//public:
//    static const Variant empty;

//    Variant(void)
//        : size{ 0 }
//        , data{ nullptr }
//    {
//    }

//    template <typename T>
//    Variant(T const& value)
//    {
//        size = sizeof(value);
//        data = new char[size];
//        memcpy(data, &value, size);
//    }

//    Variant(const Variant& v)
//    {
//        size = v.size;
//        data = new char[size];
//        memcpy(data, v.data, size);
//    }

//    ~Variant()
//    {
//        if (data != nullptr)
//        {
//            delete[] data;
//        }
//    }

//    template <typename T>
//    Variant& operator=(T const& value)
//    {
//        if (data != nullptr)
//        {
//            delete[] data;
//        }
//        size = sizeof(value);

//        data = new char[size];
//        memcpy(data, &value, size);
//        return *(this);
//    }

//    template <typename Type>
//    inline Type as()
//    {
//        return *(Type*)data;
//    }

//    template <typename Type>
//    operator Type()
//    {
//        return *(Type*)data;
//    }

//    size_t size;
//    void* data;
//};
