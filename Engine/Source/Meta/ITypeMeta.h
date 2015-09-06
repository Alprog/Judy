
#pragma once

#include <map>
#include <vector>
#include <string>

class Any;
class IFieldMeta;
class IFunctionMeta;

class ITypeMeta
{
public:
    std::string name;

    virtual bool isPointer() = 0;
    virtual bool isVector() = 0;
    virtual bool isClass() = 0;

    virtual Any CreateOnStack() = 0;
    virtual Any CreateOnHeap() = 0;

    virtual ITypeMeta* GetPointeeType() = 0;

    virtual Any Dereference(Any& object) = 0;
    virtual Any MakePointer(Any& object) = 0;
};

class IClassMeta : public ITypeMeta
{
protected:
    IClassMeta();

public:
    ITypeMeta* valueType;
    std::vector<IFunctionMeta*> constructors;
    std::map<std::string, IFieldMeta*> fields;
    std::map<std::string, IFunctionMeta*> methods;
};
