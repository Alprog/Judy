
#pragma once

#include <map>
#include <vector>
#include <string>

#include "Meta/Any.h"

class ITypeMeta
{
public:
    enum Flags
    {
        IsBuiltIn = 1 << 0,
        IsClass = 1 << 1,
        IsObject = 1 << 2,
        IsPointer = 1 << 3,
        IsPointerToObject = 1 << 4,
        IsPointerToPolymorhic = 1 << 5,
        IsRef = 1 << 6,
        IsCustomSerializing = 1 << 7
    };

    std::string name;
    virtual Flags getFlags() const = 0;
    virtual size_t getSize() const = 0;

    inline bool isClass() const { return getFlags() & Flags::IsClass; }
    inline bool isPointer() const { return getFlags() & Flags::IsPointer; }
    inline bool isRef() const { return getFlags() & Flags::IsRef; }
    inline bool isCustomSerializing() const { return getFlags() & Flags::IsCustomSerializing; }
    inline bool isObject() const { return getFlags() & Flags::IsObject; }

    virtual Any create() = 0;

    virtual ITypeMeta* getPointerType() = 0;
    virtual ITypeMeta* getPointeeType() = 0;
    virtual ITypeMeta* getRunTimePointeeType(Any object) = 0;

    virtual Any reference(Any& object) = 0;
    virtual Any dereference(Any& object) = 0;

    Any makePointer(Any& object) { return getPointerType()->reference(object); }
};
