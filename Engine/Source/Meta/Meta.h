
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

        types.push_back(meta);
        typeMap.emplace(std::type_index(typeid(T)), meta);
    }

public:
    template <typename T>
    ITypeMeta* GetMetaType()
    {
        auto index = std::type_index(typeid(T));
        auto it = typeMap.find(index);
        if (it != typeMap.end())
        {
            return it->second;
        }
        return nullptr;
    }

    template <typename T>
    inline ITypeMeta* GetMetaType(T* p)
    {
        return GetMetaType<T>();
    }

public:
    std::unordered_map<std::type_index, ITypeMeta*> typeMap;
    std::vector<ITypeMeta*> types;


};
