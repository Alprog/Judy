
#pragma once

#include <vector>
#include <unordered_map>
#include <typeindex>

class ITypeMeta;

namespace meta
{
    extern std::unordered_map<std::type_index, ITypeMeta*> types;

    /*template <typename T>
    ITpMt* OL(T* p)
    {
        auto index = std::type_index(typeid(*p));

        auto it = metas.find(index);

        if (it == metas.end())
        {

        }
        else
        {
            return it->second;
        }

        printf(typeid(*p).name());
        printf("\n");

        return nullptr;
    }*/

}


class Meta
{
public:
    static Meta* Instance();

    std::unordered_map<std::string, ITypeMeta*> TypeMap;

    std::vector<ITypeMeta*> Types;

private:
    Meta();
};
