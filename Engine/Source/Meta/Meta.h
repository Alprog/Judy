
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

    template <typename T>
    void DefineBuildInType(std::string name)
    {
        //ITypeMeta* meta = TypeMeta<T>::Instance();
        ITypeMeta* meta = new TypeMeta<T>();
        meta->name = name;

        printf("HHH %i \n", meta->isPointer());

        types.push_back(meta);
        typeMap.emplace(std::type_index(typeid(T)), meta);
    }

public:
    ITypeMeta* GetTypeMeta(std::type_index index);

    template <typename T>
    ITypeMeta* GetTypeMeta()
    {
        auto index = std::type_index(typeid(T));
        return GetTypeMeta(index);
    }

    template <typename T>
    inline ITypeMeta* GetTypeMeta(T* p)
    {
        return GetTypeMeta<T>();
    }

public:
    std::unordered_map<std::type_index, ITypeMeta*> typeMap;
    std::vector<ITypeMeta*> types;
};

