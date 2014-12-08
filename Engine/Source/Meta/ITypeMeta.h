
#pragma once

#include <vector>

class Variant;
class IFieldMeta;
class IMethodMeta;
class IConstructorMeta;

class ITypeMeta
{
public:
    char* name;
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

    virtual Variant CreateOnStack() = 0;
    virtual Variant CreateOnHeap() = 0;

    template <typename Type>
    inline static ITypeMeta* const Get()
    {
        return TypeMeta<Type>::Get();
    }

    virtual ITypeMeta* DerefType() = 0;

    virtual Variant Dereferencing(Variant& object) = 0;
    virtual Variant MakePointerTo(Variant& object) = 0;
};
