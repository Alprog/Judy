
#pragma once

#include <string>
#include "Attributes.h"

class lua_State;

class _(Meta)__ Object
{
    friend class LuaBinder;

public:
    Object();
    virtual ~Object();

    void Retain();
    void Release();

private:
    static int GC(lua_State* L);

public:
    int referenceCount;

    void* luaObject;
    _(Serialize)__ std::string luaClass;
};

