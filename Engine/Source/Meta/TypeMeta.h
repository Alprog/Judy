
#pragma once

#include <vector>
#include <type_traits>

#include "ITypeMeta.h"
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

//---

template <typename T>
struct pointerOf
{
    using type = T*;
};

template <typename T>
struct pointerOf<T*>
{
    using type = DeepPointer<typename std::decay<T>::type>;
};

template <typename T>
struct pointerOf<DeepPointer<T>>
{
    using type = DeepPointer<T>;
};

//---

template <typename T>
struct pointeeOf
{
    using type = std::nullptr_t;
};

template <typename T>
struct pointeeOf<T*>
{
    using type = T;
};

template <typename T>
struct pointeeOf<DeepPointer<T>>
{
    using type = typename DeepPointer<T>::pointeeType;
};

//---

template <typename ClassType>
class TypeMeta : public IBase<ClassType>::type, public Singleton<TypeMeta<ClassType>>
{
public:
    using pointeeType = typename pointeeOf<ClassType>::type;
    using pointerType = typename pointerOf<ClassType>::type;

    virtual ITypeMeta::Flags getFlags() const override
    {
        const int flags =
            (~is<ClassType>::Class + 1) & Flags::Class |
            (~is<ClassType>::Pointer + 1) & Flags::Pointer |
            (~is<ClassType>::PointerToPolymorhic + 1) & Flags::PointerToPolymorhic |
            (~is<ClassType>::List + 1) & Flags::List
        ;
        return (Flags)flags;
    }

    virtual Any CreateOnStack() override { return CreateOnStackHelper<ClassType>(); }
    virtual Any CreateOnHeap() override { return CreateOnHeapHelper<ClassType>(); }
    virtual Any Dereference(Any& object) override { return DereferenceHelper<ClassType>(object); }
    virtual Any MakePointer(Any& object) override { return MakePointerHelper<ClassType>(object); }
    virtual ITypeMeta* GetPointerType() override { return TypeMetaOf<pointerType>(); }
    virtual ITypeMeta* GetPointeeType() override { return TypeMetaOf<pointeeType>(); }
    virtual ITypeMeta* GetRunTimePointeeType(Any& object) override { return GetRunTimePointeeTypeHelper<ClassType>(object); }

private:
    //---------------------------------------------------------------------------------

    template <typename T>
    static inline Any CreateOnStackHelper(IF_NOT(T, Class)* = nullptr)
    {
        return T();
    }

    template <typename T>
    inline Any CreateOnStackHelper(IF(T, Class)* = nullptr)
    {
        return IClassMeta::constructors[0]->Invoke();
    }

    //---------------------------------------------------------------------------------

    template <typename T>
    static inline Any CreateOnHeapHelper(IF_NOT(T, ClassOrPointer)* = nullptr)
    {
        return new T();
    }

    template <typename T>
    static inline Any CreateOnHeapHelper(IF(T, RealPointer)* = nullptr)
    {
        return DeepPointer<typename std::remove_pointer<T>::type>(new T());
    }

    template <typename T>
    static inline Any CreateOnHeapHelper(IF(T, DeepPointer)* = nullptr)
    {
        throw std::runtime_error("not implemented");
    }

    template <typename T>
    static inline Any CreateOnHeapHelper(IF(T, Class)* = nullptr)
    {
        throw std::runtime_error("not implemented");
    }

    //---------------------------------------------------------------------------------

    template <typename T>
    static inline Any DereferenceHelper(Any& object, IF(T, AllowDereferencing)* = nullptr)
    {
        return *(object.as<T>());
    }

    template <typename T>
    static inline Any DereferenceHelper(Any& object, IF_NOT(T, AllowDereferencing)* = nullptr)
    {
        throw std::runtime_error("invalid dereferencing");
    }

    //---------------------------------------------------------------------------------

    template <typename T>
    inline Any MakePointerHelper(Any& object, IF_NOT(T, AbstractClassOrRealPointer)* = nullptr)
    {
        return &object.as<T>();
    }

    template <typename T>
    static inline Any MakePointerHelper(Any& object, IF(T, Abstract)* = nullptr)
    {
        throw std::runtime_error("invalid referencing");
    }

    template <typename T>
    static inline Any MakePointerHelper(Any& object, IF(T, RealPointer)* = nullptr)
    {
        return DeepPointer<typename std::remove_pointer<T>::type>(&object.as<T>());
    }

    //---------------------------------------------------------------------------------

    template <typename T>
    static inline ITypeMeta* GetRunTimePointeeTypeHelper(Any& object, IF(T, PointerToPolymorhic)* = nullptr)
    {
        auto pointer = object.as<T>();
        auto index = std::type_index(typeid(*pointer));
        return Meta::Instance()->Find(index);
    }

    template <typename T>
    static inline ITypeMeta* GetRunTimePointeeTypeHelper(Any& object, IF_NOT(T, PointerToPolymorhic)* = nullptr)
    {
        throw std::runtime_error("type is not real pointer");
    }

    //---------------------------------------------------------------------------------
};

template <typename T>
inline ITypeMeta* TypeMetaOf()
{
    return TypeMeta<typename std::decay<T>::type>::Instance();
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
