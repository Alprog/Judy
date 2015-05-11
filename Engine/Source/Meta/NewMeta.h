
#pragma once

#include "Sfinae.h"
#include <vector>
#include "BaseType.h"

class IConstructorMeta;
class IFieldMeta;
class IMethodMeta;

struct ITypeMETA
{
    virtual bool isPointer() { return false; }
    virtual bool isClass() { return false; }
};

struct ClassMETA : ITypeMETA
{
    virtual bool isClass() override { return true; }

    std::vector<IConstructorMeta*> constructors;
    std::vector<IFieldMeta*> fields;
    std::vector<IMethodMeta*> methods;
};

struct IPointerMETA : ITypeMETA
{
    virtual bool isPointer() override { return true; }

    IPointerMETA(ITypeMETA* pointeeType)
    {
        this->pointeeType = pointeeType;
    }

    ITypeMETA* pointeeType;
};

//---------------------------------

template <typename T, typename Enable = void>
struct TypeMetaHolder
{
    static ITypeMETA* Instance()
    {
        static ClassMETA instance;
        return &instance;
    }
};

template <typename T>
struct TypeMetaHolder<T, typename enable_pointer<T>::type>
{
    static ITypeMETA* Instance()
    {
        static IPointerMETA instance { TypeMetaOf<base_type<T>::value>() };
        return &instance;
    }
};


template <typename T>
inline ITypeMETA* TypeMetaOf()
{
    return TypeMetaHolder<T>::Instance();
}
