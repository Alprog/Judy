
#pragma once

#include "IMemberMeta.h"
#include <vector>
#include "Any.h"

class IFunctionMeta : public IMemberMeta
{
public:
    virtual ITypeMeta* getReturnType() = 0;
    virtual size_t getArgCount() = 0;
    virtual std::vector<ITypeMeta*> getArgTypes() = 0;

    virtual Any invoke(std::vector<Any>& args) = 0;

    template <typename... ArgTypes>
    inline Any invoke(ArgTypes... args)
    {
        std::vector<Any> vector{args...};
        return invoke(vector);
    }
};
