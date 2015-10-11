
#pragma once

#include "IFunctionMeta.h"
#include <vector>
#include "Any.h"

class IConstructorMeta : public virtual IFunctionMeta
{
public:
    virtual Any New(std::vector<Any>& args) = 0;
    virtual ITypeMeta* GetNewType() = 0;
};
