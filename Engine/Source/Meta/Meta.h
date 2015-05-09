
#pragma once

#include <vector>
#include <unordered_map>
#include <typeindex>
#include "Singleton.h"

class ITypeMeta;

class Meta : public Singleton<Meta>
{
    friend class Singleton<Meta>;

private:
    Meta();

public:
    template <typename T>
    ITypeMeta* GetTypeMeta(T* p)
    {
        auto index = std::type_index(typeid(*p));
        auto it = typeMap.find(index);
        if (it != typeMap.end())
        {
            return it->second;
        }
        return nullptr;
    }

public:
    std::unordered_map<std::type_index, ITypeMeta*> typeMap;
    std::vector<ITypeMeta*> types;


};
