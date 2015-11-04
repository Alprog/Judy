
#pragma once

#include <memory>
#include "Meta/Serializer.h"
#include "Attributes.h"

template <typename T>
class _(Meta)__ SmartPointer : public std::shared_ptr<T>
{
    friend class Meta;

public:
    using base = std::shared_ptr<T>;

    SmartPointer()
    {
    }

    SmartPointer(T* pointer)
        : base(pointer)
    {
    }

private:
    static void serialize(SmartPointer<T> ptr, Serializer* serializer)
    {
        serializer->Serialize(ptr.get(), TypeMetaOf<T*>());
    }

    static SmartPointer<T> deserialize(Serializer* serializer)
    {
        auto any = serializer->Deserialize(TypeMetaOf<T*>());
        auto pointer = any.as<T*>();
        return SmartPointer<T>(pointer);
    }
};
