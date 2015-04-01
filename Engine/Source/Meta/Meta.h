
#pragma once

#include <vector>
#include <unordered_map>

class ITypeMeta;

class Meta
{
public:
    static Meta* Instance();

    std::unordered_map<std::string, ITypeMeta*> TypeMap;

    std::vector<ITypeMeta*> Types;

private:
    Meta();
};
