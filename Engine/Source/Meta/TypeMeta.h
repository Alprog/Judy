
#pragma once

#include <vector>
#include <TypeTraits.h>

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
            (~is<ClassType>::BuiltIn + 1) & ITypeMeta::Flags::IsBuiltIn |
            (~is<ClassType>::Class + 1) & ITypeMeta::Flags::IsClass |
            (~is<ClassType>::Object + 1) & ITypeMeta::Flags::IsObject |
            (~is<ClassType>::Pointer + 1) & ITypeMeta::Flags::IsPointer |
            (~is<ClassType>::PointerToObject + 1) & ITypeMeta::Flags::IsPointerToObject |
            (~is<ClassType>::PointerToPolymorhic + 1) & ITypeMeta::Flags::IsPointerToPolymorhic |
            (~is<ClassType>::Ref + 1) & ITypeMeta::Flags::IsRef |
            (~is<ClassType>::Enum + 1) & ITypeMeta::Flags::IsEnum |
            (~is<ClassType>::CustomSerializing + 1) & ITypeMeta::Flags::IsCustomSerializing
        ;
        return (ITypeMeta::Flags)flags;
    }

    virtual size_t getSize() const override
    {
        return sizeof(ClassType);
    }

    virtual Any create() override { return createHelper<ClassType>(); }

    virtual Any reference(Any& pointee) override { return referenceHelper<ClassType>(pointee); }
    virtual Any dereference(Any& pointer) override { return dereferenceHelper<ClassType>(pointer); }

    virtual ITypeMeta* getPointerType() override { return typeMetaOf<pointerType>(); }
    virtual ITypeMeta* getPointeeType() override { return typeMetaOf<pointeeType>(); }
    virtual ITypeMeta* getRunTimePointeeType(Any object) override { return getRunTimePointeeTypeHelper<ClassType>(object); }

private:

    //---------------------------------------------------------------------------------

    template <typename T>
    static inline Any createHelper(IF_NOT(T, Class)* = nullptr)
    {
        return T();
    }

    template <typename T>
    inline Any createHelper(IF(T, Class)* = nullptr)
    {
        return IClassMeta::constructors[0]->invoke();
    }

    //---------------------------------------------------------------------------------

    template <typename T>
    inline Any referenceHelper(Any& pointee, IF(T, Pointer)* = nullptr)
    {
        return T((pointeeType*)pointee.getAddress());
    }

    template <typename T>
    inline Any referenceHelper(Any& /*pointee*/, IF_NOT(T, Pointer)* = nullptr)
    {
        throw std::runtime_error("not implemented");
    }

    //---------------------------------------------------------------------------------

    template <typename T>
    static inline Any dereferenceHelper(Any& pointer, IF(T, AllowDereferencing)* = nullptr)
    {
        return *(pointer.as<pointerType>());
    }

    template <typename T>
    static inline Any dereferenceHelper(Any& /*pointer*/, IF_NOT(T, AllowDereferencing)* = nullptr)
    {
        throw std::runtime_error("invalid dereferencing");
    }

    //---------------------------------------------------------------------------------

    template <typename T>
    static inline ITypeMeta* getRunTimePointeeTypeHelper(Any& object, IF(T, PointerToPolymorhic)* = nullptr)
    {
        auto baseClassMeta = (IClassMeta*)typeMetaOf<pointeeType>();
        if (baseClassMeta->hasDerives)
        {
            pointeeType* pointer = object.as<T>();
            auto index = std::type_index(typeid(*pointer));
            return Meta::getInstance()->find(index);
        }
        else
        {
            return baseClassMeta;
        }
    }

    template <typename T>
    static inline ITypeMeta* getRunTimePointeeTypeHelper(Any& /*object*/, IF_NOT(T, PointerToPolymorhic)* = nullptr)
    {
        return typeMetaOf<pointeeType>();
    }

    //---------------------------------------------------------------------------------
};

template <typename T>
inline ITypeMeta* typeMetaOf()
{
    return TypeMeta<typename fulldecay<T>::type>::getInstance();
}

template <>
inline ITypeMeta* typeMetaOf<void>()
{
    return nullptr;
}

template <>
inline ITypeMeta* typeMetaOf<std::nullptr_t>()
{
    throw std::runtime_error("invalid argument for typeMetaOf");
}
