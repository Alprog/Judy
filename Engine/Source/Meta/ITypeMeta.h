
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
    enum Flags
    {
        Class = 1 << 0,
        Pointer = 1 << 1,
        List = 1 << 2
    };

    std::string name;

    virtual Flags getFlags() = 0;

    virtual Any CreateOnStack() = 0;
    virtual Any CreateOnHeap() = 0;

    virtual ITypeMeta* GetPointeeType() = 0;

    virtual Any Dereference(Any& object) = 0;
    virtual Any MakePointer(Any& object) = 0;
};

class IClassMeta : public ITypeMeta
{
public:
    std::vector<ITypeMeta*> templateArguments;
    std::vector<ITypeMeta*> baseTypes;

    std::vector<IConstructorMeta*> constructors;
    std::map<std::string, IFieldMeta*> fields;
    std::map<std::string, IFunctionMeta*> methods;
    std::map<std::string, IFunctionMeta*> functions;
};
