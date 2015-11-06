
#pragma once

#include <string>

class Scriptable
{
    int scriptId;

    Scriptable();
    virtual ~Scriptable();
};

std::string luaClass;
