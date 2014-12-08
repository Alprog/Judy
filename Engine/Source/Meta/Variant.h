
#pragma once

#include "memory.h"
#include "stdio.h"
#include "ITypeMeta.h"

struct IVariantData
{
    virtual ~IVariantData()
    {
    }

    virtual IVariantData* copy() = 0;
};

template <typename T>
struct VariantData : public IVariantData
{
    T data;

    VariantData(T const& data)
        : data(data)
    {
    }

    virtual IVariantData* copy() override
    {
        return new VariantData<T>(data);
    }
};

class Variant
{
public:
    static const Variant empty;

    IVariantData* data;

    Variant(void)
        : data {nullptr}
    {
    }

    template <typename T>
    Variant(T const& value)
    {
        data = new VariantData<T>(value);
    }

    // copy constructor
    Variant(const Variant& other)
    {
        CopyData(other);
    }

    // move constructor
    Variant(Variant&& other)
    {
        MoveData(other);
    }

    // copy assigment operator
    Variant& operator=(const Variant& other)
    {
        DestroyData();
        CopyData(other);
        return *this;
    }

    // move assigment operator
    Variant& operator=(Variant&& other)
    {
        DestroyData();
        MoveData(other);
        return *this;
    }

    // destructor
    ~Variant()
    {
        DestroyData();
    }

    inline void DestroyData()
    {
        if (data != nullptr)
        {
            delete data;
        }
    }

    inline void CopyData(const Variant& other)
    {
        if (other.data == nullptr)
        {
            data = nullptr;
        }
        else
        {
            data = other.data->copy();
        }
    }

    inline void MoveData(Variant& other)
    {
        data = other.data;
        other.data = nullptr;
    }

    template <typename T>
    Variant& operator=(T& value)
    {
        DestroyData();

        data = new VariantData<T>(value);
        return *this;
    }

    template <typename Type>
    inline Type& as()
    {
        return static_cast<VariantData<Type>*>(data)->data;
    }

    template <typename Type>
    operator Type&()
    {
        return static_cast<VariantData<Type>*>(data)->data;
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
