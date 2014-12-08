
#pragma once

#include "ITypeMeta.h"
#include "VariantData.h"

class Variant
{
public:
    static const Variant empty;

    Variant(void)
        : data {nullptr}
    {
    }

    template <typename T>
    Variant(T const& value)
    {
        data = new VariantData<T>(value);
    }

    // Rule of Five
    Variant(const Variant& other);             // copy constructor
    Variant(Variant&& other);                  // move constructor
    Variant& operator=(const Variant& other);  // copy assigment operator
    Variant& operator=(Variant&& other);       // move assigment operator
    ~Variant();                                // destructor

private:
    inline void DestroyData();
    inline void CopyData(const Variant& other);
    inline void MoveData(Variant& other);

public:
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

    inline ITypeMeta* GetType()
    {
        if (data != nullptr)
        {
            return data->GetType();
        }
        else
        {
            return nullptr;
        }
    }

private:
    IVariantData* data;
};
