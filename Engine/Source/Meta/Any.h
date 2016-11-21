
#pragma once

#include "AnyData.h"

class ITypeMeta;

class Any
{
public:
    static const Any empty;

    Any(void);

    template <typename T>
    Any(T const& value)
    {
        data = new AnyData<T>(value);
    }

    // Rule of Five
    Any(const Any& other);             // copy constructor
    Any(Any&& other);                  // move constructor
    Any& operator=(const Any& other);  // copy assigment operator
    Any& operator=(Any&& other);       // move assigment operator
    ~Any();                            // destructor

    void detach(); // detach data (it will not be deleted)

private:
    inline void destroyData();
    inline void copyData(const Any& other);
    inline void moveData(Any& other);

public:
    template <typename T>
    Any& operator=(T& value)
    {
        destroyData();

        data = new AnyData<T>(value);
        return *this;
    }

    template <typename Type>
    inline Type& as()
    {
        return static_cast<AnyData<Type>*>(data)->data;
    }

    template <typename Type>
    operator Type&()
    {
        return static_cast<AnyData<Type>*>(data)->data;
    }

    inline ITypeMeta* getType()
    {
        if (data != nullptr)
        {
            return data->getType();
        }
        else
        {
            return nullptr;
        }
    }

    inline void* getAddress()
    {
        return &static_cast<AnyData<void*>*>(data)->data;
    }

private:
    IAnyData* data;
};
