
#pragma once

#include "IMemberMeta.h"
#include "ITypeMeta.h"

class IPropertyMeta : public IMemberMeta
{
public:
    virtual void Set(Any& object, Any& value) = 0;
    virtual Any Get(Any& object) = 0;
    virtual ITypeMeta* const GetType() = 0;
};
