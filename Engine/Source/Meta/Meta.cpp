
#include "Meta.h"

std::unordered_map<std::type_index, ITypeMeta*> meta::types;

Meta* Meta::Instance()
{
    static Meta instance;
    return &instance;
}
