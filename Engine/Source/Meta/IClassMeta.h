
#pragma once

#include "ITypeMeta.h"
#include <vector>
#include <string>
#include <unordered_map>

class IFieldMeta;
class IFunctionMeta;
class IConstructorMeta;
class PropertyMeta;
template <typename> class List;

class IClassMeta : public ITypeMeta
{
public:
    std::vector<ITypeMeta*> templateArguments;
    std::vector<ITypeMeta*> baseTypes;

    std::vector<IConstructorMeta*> constructors;
    std::unordered_map<std::string, IFunctionMeta*> methods;
    std::unordered_map<std::string, IFunctionMeta*> functions;
    std::unordered_map<std::string, IFieldMeta*> fields;
    std::unordered_map<std::string, PropertyMeta*> properties;

    List<IFieldMeta*> GetFieldsWithAttribute(std::string attribute, bool includeProperties = false);
};
