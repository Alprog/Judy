
#pragma once

#include "IMemberMeta.h"
#include "FunctionMeta.h"
#include "IFieldMeta.h"

class PropertyMeta : public IFieldMeta
{
public:
    PropertyMeta(std::string name);

    virtual void Set(Any& object, Any& value) override;
    virtual Any Get(Any& object) override;
    virtual ITypeMeta* const GetType() override;

    IFunctionMeta* getter;
    IFunctionMeta* setter;
};
