
#include "Meta.h"
#include "TypeMeta.h"

#include "ClassDefiner.h"
#include "CallInfo.h"
#include "Node.h"

void Meta::Init()
{
    DefineBuildInType<bool>("bool");
    DefineBuildInType<int>("int");
    DefineBuildInType<float>("float");
    DefineBuildInType<std::string>("string");
    DefineBuildInType<char>("char");
    DefineBuildInType<double>("double");

    DefineClasses();
}

ITypeMeta* Meta::Find(std::type_index index)
{
    auto it = typeMap.find(index);
    if (it != std::end(typeMap))
    {
        return it->second;
    }
    return nullptr;
}
