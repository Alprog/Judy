
#pragma once

#include <vector>
#include "Variant.h"

class IFieldMeta;
class IMethodMeta;
class IConstructorMeta;

class ITypeMeta
{
public:
    char* name;

    void set(void* object, char* name, void* value);
    void* get(void* object, char* name);

    Variant invoke(void* object, char* name, std::vector<Variant> args);

    std::vector<IConstructorMeta*> constructors;
    std::vector<IFieldMeta*> fields;
    std::vector<IMethodMeta*> methods;

    virtual bool isPointer() = 0;
    virtual Variant DefaultConstructor() = 0;

    template <typename Type>
    static ITypeMeta* Get()
    {
        return TypeMeta<Type>::Instance();
    }
};

template <typename Type>
class TypeMeta : public ITypeMeta
{
public:
    static TypeMeta* Instance()
    {
        static TypeMeta<Type> instance;
        return &instance;
    }

    ITypeMeta* PointerType()
    {
        return TypeMeta<Type*>::Instance();
    }

    virtual bool isPointer() override
    {
        return false;
    }

    Variant DefaultConstructor() override
    {
        return new Type();
    }

    template <typename... Types>
    inline static Type* New(Types... args)
    {
        return new Type(args...);
    }
};

template <typename Type>
class BuildInTypeMeta : TypeMeta<Type>
{
};

template <typename Type>
class ClassMeta : TypeMeta<Type>
{
};

template <typename Type>
class PointerTypeMeta : TypeMeta<Type>
{
};


/*template <typename Type>
class TypeMeta<Type*> : public ITypeMeta
{
public:
    static TypeMeta* Instance()
    {
        static TypeMeta<Type*> instance;
        return &instance;
    }

    virtual bool isPointer() override
    {
        return true;
    }

    Variant DefaultConstructor() override
    {
        return new Type();
    }
};*/
