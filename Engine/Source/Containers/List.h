
#pragma once

#include <vector>
#include "Meta/Serializer.h"
#include "Lua.h"
#include "Attributes.h"

template <typename T>
class [[Meta]] List : public std::vector<T>
{
    friend class Meta;
    using base = std::vector<T>;

public:
    inline List() = default;

    inline List(size_t count)
        : base(count)
    {
    }

    inline List(std::initializer_list<T> items)
        : base(items)
    {
    }

    inline T& at(int index) { return base::at(index); }
    inline void add(T value) { base::push_back(value); }

private:
    friend typename std::vector<T>::iterator begin(List<T>* list) { return list->begin(); }
    friend typename std::vector<T>::iterator end(List<T>* list) { return list->end(); }

    static void serialize(List<T> list, Serializer* serializer)
    {
        auto L = serializer->getL();
        auto valueType = TypeMetaOf<T>();
        lua_newtable(L);
        for (auto i = 0; i < list.size(); i++)
        {
            auto value = list[i];
            serializer->Serialize(value, valueType);
            lua_seti(L, -2, i + 1);
        }
    }

    static List<T> deserialize(Serializer* serializer)
    {
        auto L = serializer->getL();
        auto valueType = TypeMetaOf<T>();

        List<T> list;
        lua_pushnil(L);
        while (lua_next(L, -2) != 0)
        {
            auto value = serializer->Deserialize(valueType);
            list.add(value);
            lua_pop(L, 1);
        }

        return list;
    }
};
