
#pragma once

#include <vector>
#include <type_traits>

#include "ITypeMeta.h"
#include "Any.h"
#include "Singleton.h"
#include "DeepPointer.h"

#include "ConstructorMeta.h"

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
    virtual bool isPointer() override { return is<ClassType>::Pointer; }
    virtual bool isClass() override { return is<ClassType>::Class; }
    virtual bool isVector() override { return false; }

    virtual Any CreateOnStack() override { return CreateOnStackHelper<ClassType>(); }
    virtual Any CreateOnHeap() override { return CreateOnHeapHelper<ClassType>(); }
    virtual Any Dereference(Any& object) override { return DereferenceHelper<ClassType>(object); }
    virtual Any MakePointer(Any& object) override { return MakePointerHelper<ClassType>(object); }
    virtual ITypeMeta* GetPointeeType() override { return GetPointeeTypeHelper<ClassType>(); }

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
        std::vector<Any> args;
        return IClassMeta::constructors[0]->Invoke(args);
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
    static inline ITypeMeta* GetPointeeTypeHelper(IF_NOT(T, Pointer)* = nullptr)
    {
        throw std::runtime_error("type is not pointer");
    }

    template <typename T>
    static inline ITypeMeta* GetPointeeTypeHelper(IF(T, RealPointer)* = nullptr)
    {
        return TypeMetaOf<typename std::remove_pointer<T>::type>();
    }

    template <typename T>
    static inline ITypeMeta* GetPointeeTypeHelper(IF(T, DeepPointer)* = nullptr)
    {
        return TypeMetaOf<typename T::pointeeType>();
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
