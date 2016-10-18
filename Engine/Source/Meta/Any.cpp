
#include "Any.h"

const Any Any::empty;

Any::Any(void)
    : data {nullptr}
{
}

// copy constructor
Any::Any(const Any& other)
{
    copyData(other);
}

// move constructor
Any::Any(Any&& other)
{
    moveData(other);
}

// copy assigment operator
Any& Any::operator=(const Any& other)
{
    destroyData();
    copyData(other);
    return *this;
}

// move assigment operator
Any& Any::operator=(Any&& other)
{
    destroyData();
    moveData(other);
    return *this;
}

// destructor
Any::~Any()
{
    destroyData();
}

void Any::detach()
{
    data = nullptr;
}

inline void Any::destroyData()
{
    if (data != nullptr)
    {
        delete data;
    }
}

inline void Any::copyData(const Any& other)
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

inline void Any::moveData(Any& other)
{
    data = other.data;
    other.data = nullptr;
}
