
#pragma once

#include <vector>
#include <unordered_map>
#include <typeindex>
#include "Singleton.h"
#include "TypeMeta.h"

class ITypeMeta;

class Meta : public Singleton<Meta>
{
    friend class Singleton<Meta>;

private:
    Meta();

    template <typename T>
    void DefineBuildInType(std::string name)
    {
        ITypeMeta* meta = TypeMeta<T>::Instance();
        meta->name = name;
    }

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
