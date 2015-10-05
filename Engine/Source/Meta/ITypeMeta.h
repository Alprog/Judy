
#pragma once

#include <map>
#include <vector>
#include <string>

class Any;
class IFieldMeta;
class IFunctionMeta;
class IConstructorMeta;

class ITypeMeta
{
public:
    std::string name;

    virtual bool isPointer() = 0;
    virtual bool isClass() = 0;
    virtual bool isList() = 0;
    virtual bool isArray() = 0;
    virtual bool isMap() = 0;

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
    std::vector<ITypeMeta*> templateArguments;

    std::vector<IConstructorMeta*> constructors;
    std::map<std::string, IFieldMeta*> fields;
    std::map<std::string, IFunctionMeta*> methods;
    std::map<std::string, IFunctionMeta*> functions;
};
