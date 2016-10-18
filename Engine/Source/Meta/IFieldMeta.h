
#pragma once

#include "IMemberMeta.h"
#include "ITypeMeta.h"

class IFieldMeta : public IMemberMeta
{
public:
    virtual void set(Any& object, Any& value) = 0;
    virtual Any get(Any& object) = 0;
    virtual Any getAddr(Any& object) = 0;
    virtual ITypeMeta* const getType() = 0;
};
