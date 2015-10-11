
#pragma once

#include "IMemberMeta.h"
#include "FunctionMeta.h"

class PropertyMeta : public IMemberMeta
{
public:
    PropertyMeta(std::string name);

    IFunctionMeta* getter;
    IFunctionMeta* setter;
};
