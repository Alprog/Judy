
#pragma once

#include "Object.h"
#include "Attributes.h"
#include "Meta/Serializer.h"
#include "DeepPointer.h"

template <typename T>
class _(Meta)__ Ref
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
        Retain();
	}

	// normal assign operator
    Ref<T>& operator=(T* value)
	{
        Release();
		pointer = value;
        Retain();
		return *this;
	}

	// copy constructor
    Ref(const Ref<T>& other)
	{
        Copy(other);
	}

	// move constructor
    Ref(Ref<T>&& other)
	{
        Move(other);
	}

	// copy assigment operator 
    Ref<T>& operator=(const Ref<T>& other)
	{
        Release();
        Copy(other);
		return *this;
	}

	// move assigment operator 
    Ref<T>& operator=(Ref<T>&& other)
	{
        Release();
        Move(other);
		return *this;
	}

	// destructor
    ~Ref()
	{
        Release();
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

    T* Get() const
	{
		return pointer;
	}

private:
    inline void Retain()
	{
		if (pointer != nullptr)
		{
            pointer->Retain();
		}
	}

    inline void Release()
	{
		if (pointer != nullptr)
		{
            pointer->Release();
		}
	}

    inline void Copy(const Ref<T>& other)
	{
		pointer = other.pointer;
		if (pointer != nullptr)
		{
            pointer->Retain();
		}
	}

    inline void Move(Ref<T>& other)
	{
		pointer = other.pointer;
		other.pointer = nullptr;
	}

private:
    static void serialize(Ref<T> ref, Serializer* serializer)
    {
        serializer->Serialize(ref.pointer, TypeMetaOf<T*>());
    }

    static Ref<T> deserialize(Serializer* serializer)
    {
        auto any = serializer->Deserialize(TypeMetaOf<T*>());
        return Ref<T>(any.as<T*>());
    }

    T* pointer;
};
