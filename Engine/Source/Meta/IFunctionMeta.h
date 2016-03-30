
#pragma once

#include "IMemberMeta.h"
#include <vector>
#include "Any.h"

class IFunctionMeta : public IMemberMeta
{
public:
    virtual ITypeMeta* GetReturnType() = 0;
    virtual size_t GetArgCount() = 0;
    virtual std::vector<ITypeMeta*> GetArgTypes() = 0;

    virtual Any Invoke(std::vector<Any>& args) = 0;

    template <typename... ArgTypes>
    inline Any Invoke(ArgTypes... args)
    {
        std::vector<Any> vector{args...};
        return Invoke(vector);
    }
};
