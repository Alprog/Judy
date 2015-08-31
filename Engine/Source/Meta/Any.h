
#pragma once

#include "AnyData.h"
#include "Sfinae.h"
#include <exception>

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

//---------------------------------------------------------------------------------

template <typename T>
inline Any Deref(Any& object, IF(T, AllowDereferencing)* = nullptr)
{
    return *(object.as<T>());
}

template <typename T>
inline Any Deref(Any& object, IF_NOT(T, AllowDereferencing)* = nullptr)
{
    throw std::exception("invalid dereferencing");
}

//---------------------------------------------------------------------------------

template <typename T>
inline Any MakePtr(Any& object, IF_NOT(T, AbstractClassOrRealPointer)* = nullptr)
{
    return &object.as<T>();
}

template <typename T>
inline Any MakePtr(Any& object, IF(T, Abstract)* = nullptr)
{
    throw std::exception("invalid referencing");
}

template <typename T>
inline Any MakePtr(Any& object, IF(T, RealPointer)* = nullptr)
{
    return DeepPointer<std::remove_pointer<T>::type>(&object.as<T>());
}
