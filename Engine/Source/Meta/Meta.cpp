
#include "Meta.h"
#include "TypeMeta.h"

#include "ClassDefiner.h"
#include "CallInfo.h"
#include "Node.h"

void Meta::init()
{
    defineBuildInType<bool>("bool");
    defineBuildInType<int>("int");
    defineBuildInType<float>("float");
    defineBuildInType<std::string>("string");
    defineBuildInType<char>("char");
    defineBuildInType<double>("double");

    defineClasses();
}

ITypeMeta* Meta::find(std::type_index index)
{
    auto it = typeMap.find(index);
    if (it != std::end(typeMap))
    {
        return it->second;
    }
    return nullptr;
}
