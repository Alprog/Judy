
#pragma once

#include <vector>

class ITypeMeta;

class Meta
{
public:
    static Meta* Instance();

    std::vector<ITypeMeta*> Types;

private:
    Meta();
};
