
#pragma once

#include <string>
#include "Attributes.h"

class _(Meta)__ Scriptable
{
public:
    Scriptable();
    virtual ~Scriptable();

public:
    void* luaObject;
    _(Serialize)__ std::string luaClass;
};

