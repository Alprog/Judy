
#pragma once

#include <memory>
#include "Meta/Serializer.h"
#include "Attributes.h"

template <typename T>
class _(Meta)__ SmartPointer : public std::shared_ptr<T>
{
public:
    using base = std::shared_ptr<T>;

    SmartPointer(T* pointer)
        : base(pointer)
    {
    }

private:
    static void serialize(std::shared_ptr<T> ptr, Serializer* serializer)
    {
        serializer->Serialize(ptr.get(), TypeMetaOf<T*>());
    }

    static std::shared_ptr<T> deserialize(Serializer* serializer)
    {
        return serializer->Deserialize(TypeMetaOf<T*>()).as<T*>();
    }
};
