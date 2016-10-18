
#pragma once

#include "Object.h"
#include "Attributes.h"
#include "Meta/Serializer.h"
#include "DeepPointer.h"

template <typename T>
class Ref
{
    friend class Meta;

public:
    using pointeeType = T;

	// default constructor
    Ref(void)
		: pointer { nullptr }
	{
	}
	
	// normal constructor
    Ref(T* value)
		: pointer { value }
	{
        retain();
	}

	// normal assign operator
    Ref<T>& operator=(T* value)
	{
        release();
		pointer = value;
        retain();
		return *this;
	}

	// copy constructor
    Ref(const Ref<T>& other)
	{
        copy(other);
	}

	// move constructor
    Ref(Ref<T>&& other)
	{
        move(other);
	}

	// copy assigment operator 
    Ref<T>& operator=(const Ref<T>& other)
	{
        release();
        copy(other);
		return *this;
	}

	// move assigment operator 
    Ref<T>& operator=(Ref<T>&& other)
	{
        release();
        move(other);
		return *this;
	}

	// destructor
    ~Ref()
	{
        release();
	}

	T& operator*()
	{
		return *pointer;
	}

	const T& operator*() const
	{
		return *pointer;
	}

    const DeepPointer<T> operator&() const
    {
        auto ptr = const_cast<T*>(pointer);
        return DeepPointer<T>(&ptr, 2);
    }

	T* operator->()
	{
		return pointer;
	}

	const T* operator->() const
	{
		return pointer;
	}

	operator T*&()
	{
		return pointer;
	}

	bool operator==(T* value)
	{
		return pointer == value;
	}

	bool operator!=(T* value)
	{
		return pointer != value;
	}

	/*template <typename Type>
	operator Type&()
	{
		return static_cast<Type>(pointer);
	}*/

    T* get() const
	{
		return pointer;
	}

private:
    inline void retain()
	{
		if (pointer != nullptr)
		{
            pointer->retain();
		}
	}

    inline void release()
	{
		if (pointer != nullptr)
		{
            pointer->release();
		}
	}

    inline void copy(const Ref<T>& other)
	{
		pointer = other.pointer;
		if (pointer != nullptr)
		{
            pointer->retain();
		}
	}

    inline void move(Ref<T>& other)
	{
		pointer = other.pointer;
		other.pointer = nullptr;
	}

private:
    T* pointer;
};
