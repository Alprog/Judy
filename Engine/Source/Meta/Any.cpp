
#include "Any.h"

const Any Any::empty;

Any::Any(void)
    : data {nullptr}
{
}

// copy constructor
Any::Any(const Any& other)
{
    CopyData(other);
}

// move constructor
Any::Any(Any&& other)
{
    MoveData(other);
}

// copy assigment operator
Any& Any::operator=(const Any& other)
{
    DestroyData();
    CopyData(other);
    return *this;
}

// move assigment operator
Any& Any::operator=(Any&& other)
{
    DestroyData();
    MoveData(other);
    return *this;
}

// destructor
Any::~Any()
{
    DestroyData();
}

void Any::Detach()
{
    data = nullptr;
}

inline void Any::DestroyData()
{
    if (data != nullptr)
    {
        delete data;
    }
}

inline void Any::CopyData(const Any& other)
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

inline void Any::MoveData(Any& other)
{
    data = other.data;
    other.data = nullptr;
}
