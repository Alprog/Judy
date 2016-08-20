
#pragma once

#include <vector>
#include <type_traits>

#include "ITypeMeta.h"
#include "IClassMeta.h"
#include "Any.h"
#include "Singleton.h"
#include "DeepPointer.h"

#include "ConstructorMeta.h"
#include <typeindex>

template <typename T, typename Enable = void>
struct IBase
{
    using type = ITypeMeta;
};

template <typename T>
struct IBase<T, IF(T, Class)>
{
    using type = IClassMeta;
};

template <typename ClassType>
class TypeMeta : public IBase<ClassType>::type, public Singleton<TypeMeta<ClassType>>
{
public:
    using pointeeType = typename pointeeOf<ClassType>::type;
    using pointerType = typename pointerOf<ClassType>::type;

    virtual ITypeMeta::Flags getFlags() const override
    {
        const int flags =
            (~is<ClassType>::Class + 1) & ITypeMeta::Flags::IsClass |
            (~is<ClassType>::Pointer + 1) & ITypeMeta::Flags::IsPointer |
            (~is<ClassType>::Ref + 1) & ITypeMeta::Flags::IsRef |
            (~is<ClassType>::PointerToPolymorhic + 1) & ITypeMeta::Flags::IsPointerToPolymorhic |
            (~is<ClassType>::CustomSerializing + 1) & ITypeMeta::Flags::IsCustomSerializing
        ;
        return (ITypeMeta::Flags)flags;
    }


    virtual Any Create() override { return CreateHelper<ClassType>(); }

    virtual Any Reference(Any& pointee) override { return ReferenceHelper<ClassType>(pointee); }
    virtual Any Dereference(Any& pointer) override { return DereferenceHelper<ClassType>(pointer); }

    virtual ITypeMeta* GetPointerType() override { return TypeMetaOf<pointerType>(); }
    virtual ITypeMeta* GetPointeeType() override { return TypeMetaOf<pointeeType>(); }
    virtual ITypeMeta* GetRunTimePointeeType(Any object) override { return GetRunTimePointeeTypeHelper<ClassType>(object); }

private:

    //---------------------------------------------------------------------------------

    template <typename T>
    static inline Any CreateHelper(IF_NOT(T, Class)* = nullptr)
    {
        return T();
    }

    template <typename T>
    inline Any CreateHelper(IF(T, Class)* = nullptr)
    {
        return IClassMeta::constructors[0]->Invoke();
    }

    //---------------------------------------------------------------------------------

    template <typename T>
    inline Any ReferenceHelper(Any& pointee, IF(T, Pointer)* = nullptr)
    {
        return T((pointeeType*)pointee.getAddress());
    }

    template <typename T>
    inline Any ReferenceHelper(Any& /*pointee*/, IF_NOT(T, Pointer)* = nullptr)
    {
        throw std::runtime_error("not implemented");
    }

    //---------------------------------------------------------------------------------

    template <typename T>
    static inline Any DereferenceHelper(Any& pointer, IF(T, AllowDereferencing)* = nullptr)
    {
        return *(pointer.as<pointerType>());
    }

    template <typename T>
    static inline Any DereferenceHelper(Any& /*pointer*/, IF_NOT(T, AllowDereferencing)* = nullptr)
    {
        throw std::runtime_error("invalid dereferencing");
    }

    //---------------------------------------------------------------------------------

    template <typename T>
    static inline ITypeMeta* GetRunTimePointeeTypeHelper(Any& object, IF(T, PointerToPolymorhic)* = nullptr)
    {
        auto baseClassMeta = (IClassMeta*)TypeMetaOf<pointeeType>();
        if (baseClassMeta->hasDerives)
        {
            pointeeType* pointer = object.as<T>();
            auto index = std::type_index(typeid(*pointer));
            return Meta::Instance()->Find(index);
        }
        else
        {
            return baseClassMeta;
        }
    }

    template <typename T>
    static inline ITypeMeta* GetRunTimePointeeTypeHelper(Any& /*object*/, IF_NOT(T, PointerToPolymorhic)* = nullptr)
    {
        return TypeMetaOf<pointeeType>();
    }

    //---------------------------------------------------------------------------------
};

template <typename T>
inline ITypeMeta* TypeMetaOf()
{
    return TypeMeta<typename fulldecay<T>::type>::Instance();
}

template <>
inline ITypeMeta* TypeMetaOf<void>()
{
    return nullptr;
}

template <>
inline ITypeMeta* TypeMetaOf<std::nullptr_t>()
{
    throw std::runtime_error("invalid argument for TypeMetaOf");
}
