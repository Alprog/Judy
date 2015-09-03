
#pragma once

#include <vector>
#include <string>
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
        types.push_back(meta);
        typeMap.emplace(std::type_index(typeid(T)), meta);
    }

    #include "Meta.gen.h"

public:
    template <typename T, typename... Types>
    inline static T Create(Types... args)
    {
        return T(args...);
    }

    template <typename T, typename... Types>
    inline static T* CreateNew(Types... args)
    {
        return new T(args...);
    }

public:
    std::unordered_map<std::type_index, ITypeMeta*> typeMap;
    std::vector<ITypeMeta*> types;
};

