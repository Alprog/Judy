
#include "Meta.h"


ITypeMeta* Meta::GetTypeMeta(std::type_index index)
{
    auto it = typeMap.find(index);
    if (it != typeMap.end())
    {
        return it->second;
    }

    printf("NO META FOR TYPE %s \n", index.name());

    return nullptr;
}
