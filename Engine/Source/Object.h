
#pragma once

#include <string>
#include "Attributes.h"

class _(Meta)__ Object
{
public:
    Object();
    virtual ~Object();

    void Retain();
    void Release();

public:
    int referenceCount;

    void* luaObject;
    _(Serialize)__ std::string luaClass;
};

