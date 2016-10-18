
#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <typeindex>
#include "Singleton.h"

class ITypeMeta;

template <typename T>
inline ITypeMeta* typeMetaOf();

class Meta : public Singleton<Meta>
{
    friend class Singleton<Meta>;

public:
    void init();

private:
    #include "Meta.gen.h"
    void defineClasses();

    template <typename T>
    void defineBuildInType(std::string name)
    {
        auto meta = typeMetaOf<T>();
        meta->name = name;
        types.push_back(meta);
        typeMap.emplace(std::type_index(typeid(T)), meta);
    }

public:
    template <typename T, typename... Types>
    inline static T create(Types... args)
    {
        return T(args...);
    }

    template <typename T, typename... Types>
    inline static T* createNew(Types... args)
    {
        return new T(args...);
    }

    ITypeMeta* find(std::type_index index);

public:
    std::unordered_map<std::type_index, ITypeMeta*> typeMap;
    std::vector<ITypeMeta*> types;
};

