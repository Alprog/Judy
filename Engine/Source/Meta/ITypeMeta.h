
#pragma once

#include <map>
#include <vector>
#include <string>

class Any;

class ITypeMeta
{
public:
    enum Flags
    {
        IsClass = 1 << 0,
        IsPointer = 1 << 1,
        IsPointerToPolymorhic = 1 << 2,
        IsCustomSerializing = 1 << 3
    };

    std::string name;
    virtual Flags getFlags() const = 0;

    inline bool isClass() const { return getFlags() & Flags::IsClass; }
    inline bool isPointer() const { return getFlags() & Flags::IsPointer; }
    inline bool isCustomSerializing() const { return getFlags() & Flags::IsCustomSerializing; }

    virtual Any CreateOnStack() = 0;
    virtual Any CreateOnHeap() = 0;

    virtual ITypeMeta* GetPointerType() = 0;
    virtual ITypeMeta* GetPointeeType() = 0;
    virtual ITypeMeta* GetRunTimePointeeType(Any& object) = 0;

    virtual Any Dereference(Any& object) = 0;
    virtual Any MakePointer(Any& object) = 0;
};
