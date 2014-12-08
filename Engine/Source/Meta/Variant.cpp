
#include "Variant.h"

const Variant Variant::empty;

// copy constructor
Variant::Variant(const Variant& other)
{
    CopyData(other);
}

// move constructor
Variant::Variant(Variant&& other)
{
    MoveData(other);
}

// copy assigment operator
Variant& Variant::operator=(const Variant& other)
{
    DestroyData();
    CopyData(other);
    return *this;
}

// move assigment operator
Variant& Variant::operator=(Variant&& other)
{
    DestroyData();
    MoveData(other);
    return *this;
}

// destructor
Variant::~Variant()
{
    DestroyData();
}

inline void Variant::DestroyData()
{
    if (data != nullptr)
    {
        delete data;
    }
}

inline void Variant::CopyData(const Variant& other)
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

inline void Variant::MoveData(Variant& other)
{
    data = other.data;
    other.data = nullptr;
}

inline ITypeMeta* Variant::GetType()
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
