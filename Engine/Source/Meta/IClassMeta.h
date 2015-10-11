
#pragma once

#include "ITypeMeta.h"
#include <vector>
#include <unordered_map>

class IClassMeta : public ITypeMeta
{
public:
    std::vector<ITypeMeta*> templateArguments;
    std::vector<ITypeMeta*> baseTypes;

    std::vector<IConstructorMeta*> constructors;
    std::unordered_map<std::string, IFunctionMeta*> methods;
    std::unordered_map<std::string, IFunctionMeta*> functions;
    std::unordered_map<std::string, IPropertyMeta*> fields;
    std::unordered_map<std::string, IPropertyMeta*> properties;
};
