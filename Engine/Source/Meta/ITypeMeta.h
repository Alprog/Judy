
#pragma once

#include <vector>

class Any;
class IFieldMeta;
class IMethodMeta;
class IConstructorMeta;

class ITypeMeta
{
public:
    const char* name;
    bool isClass;

    ITypeMeta();

    //void set(void* object, char* name, void* value);
    //void* get(void* object, char* name);
    //Variant invoke(void* object, char* name, std::vector<Variant> args);

    std::vector<IConstructorMeta*> constructors;
    std::vector<IFieldMeta*> fields;
    std::vector<IMethodMeta*> methods;

    virtual bool isPointer() = 0;
    virtual bool isVector() = 0;

    virtual Any CreateOnStack() = 0;
    virtual Any CreateOnHeap() = 0;

    template <typename Type>
    inline static ITypeMeta* const Get()
    {
        return TypeMeta<Type>::Get();
    }

    template <>
    inline static ITypeMeta* const Get<void>()
    {
        return nullptr;
    }

    virtual ITypeMeta* DerefType() = 0;

    virtual Any Dereferencing(Any& object) = 0;
    virtual Any MakePointerTo(Any& object) = 0;
};
