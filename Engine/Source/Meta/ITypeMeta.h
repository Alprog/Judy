
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
        IsRef = 1 << 3,
        IsCustomSerializing = 1 << 4
    };

    std::string name;
    virtual Flags getFlags() const = 0;

    inline bool isClass() const { return getFlags() & Flags::IsClass; }
    inline bool isPointer() const { return getFlags() & Flags::IsPointer; }
    inline bool isRef() const { return getFlags() & Flags::IsRef; }
    inline bool isCustomSerializing() const { return getFlags() & Flags::IsCustomSerializing; }

    virtual Any Create(Any& pointee) = 0;
    virtual Any CreateOnStack() = 0;
    virtual Any CreateOnHeap() = 0;

    virtual ITypeMeta* GetPointerType() = 0;
    virtual ITypeMeta* GetPointeeType() = 0;
    virtual ITypeMeta* GetRunTimePointeeType(Any object) = 0;

    virtual Any Dereference(Any& object) = 0;
    virtual Any MakePointer(Any& object) = 0;
};
