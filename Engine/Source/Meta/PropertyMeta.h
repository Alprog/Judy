
#pragma once

#include "IMemberMeta.h"
#include "FunctionMeta.h"
#include "IPropertyMeta.h"

class PropertyMeta : public IPropertyMeta
{
public:
    PropertyMeta(std::string name);

    virtual void Set(Any& object, Any& value) override;
    virtual Any Get(Any& object) override;
    virtual ITypeMeta* const GetType() override;

    IFunctionMeta* getter;
    IFunctionMeta* setter;
};
