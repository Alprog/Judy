
#pragma once

#include <vector>
#include <string>

class Any;
class IFieldMeta;
class IMethodMeta;
class IConstructorMeta;

class ITypeMeta
{
public:
    std::string name;

    virtual bool isPointer() = 0;
    virtual bool isVector() = 0;
    virtual bool isClass() = 0;

    virtual Any CreateOnStack() = 0;
    virtual Any CreateOnHeap() = 0;

    virtual ITypeMeta* PointeeTypeMeta() = 0;

    virtual Any Dereferencing(Any& object) = 0;
    virtual Any MakePointerTo(Any& object) = 0;
};

class IClassMeta : public ITypeMeta
{
public:
    std::vector<IConstructorMeta*> constructors;
    std::vector<IFieldMeta*> fields;
    std::vector<IMethodMeta*> methods;
};
