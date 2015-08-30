
#pragma once

#include "AnyData.h"
#include "Sfinae.h"

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

private:
    inline void DestroyData();
    inline void CopyData(const Any& other);
    inline void MoveData(Any& other);

public:
    template <typename T>
    Any& operator=(T& value)
    {
        DestroyData();

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
    IAnyData* data;
};

template <typename T, typename Enable = void>
struct Dereferencer
{
    inline static Any Do(Any& object)
    {
        throw new std::exception();
    }
};

template <typename T>
struct Dereferencer<T, typename enable_pointer<T>::type>
{
    inline static Any Do(Any& object)
    {
        return *(object.as<T>());
    }
};

template <typename T>
Any Dereferencing(Any& object)
{
    return Dereferencer::Do(object);
}

//template <typename T>
//IF(std::is_pointer<T>, Any) Dereferencing(Any& object)
//{
//    return *(object.as<T*>());
//}
