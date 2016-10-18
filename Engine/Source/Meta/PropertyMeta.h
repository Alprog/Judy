
#pragma once

#include "IMemberMeta.h"
#include "FunctionMeta.h"
#include "IFieldMeta.h"

class PropertyMeta : public IFieldMeta
{
public:
    PropertyMeta(std::string name);

    virtual void set(Any& object, Any& value) override;
    virtual Any get(Any& object) override;
    virtual Any getAddr(Any& object) override;
    virtual ITypeMeta* const getType() override;

    IFunctionMeta* getter;
    IFunctionMeta* setter;
};
