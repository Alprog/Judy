
#pragma once

#include <vector>
#include <unordered_map>
#include <typeindex>
#include "Singleton.h"

class ITypeMeta;
template <typename T>
ITypeMeta* TypeMetaOf();

class Meta : public Singleton<Meta>
{
    friend class Singleton<Meta>;

private:
    Meta();

    template <typename T>
    void DefineBuildInType(std::string name)
    {
        auto meta = TypeMetaOf<T>();
        meta->name = name;

        printf("HHH %i \n", meta->isPointer());

        types.push_back(meta);
        typeMap.emplace(std::type_index(typeid(T)), meta);
    }

public:
    ITypeMeta* GetTypeMeta(std::type_index index);

    void Init();

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

    template <typename T, typename... Types>
    inline static T* New(Types... args)
    {
        return new T(args...);
    }

public:
    std::unordered_map<std::type_index, ITypeMeta*> typeMap;
    std::vector<ITypeMeta*> types;
};

