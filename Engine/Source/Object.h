
#pragma once

#include <string>
#include "Attributes.h"

struct lua_State;

class [[Meta]] Object
{
    friend class LuaBinder;

public:
    Object();
    virtual ~Object();

    void retain();
    void release();

private:
    [[Ignore]] static int GC(lua_State* L);

public:
    int referenceCount;

    void* luaObject;
    [[Serialize]] std::string luaClass;
};

