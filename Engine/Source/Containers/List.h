
#pragma once

#include <vector>
#include "Meta/Serializer.h"
#include "Lua.h"

#define __Meta__
#define __Serialize__

template <typename T>
__Meta__ class List : public std::vector<T>
{
    friend class Meta;
    using base = std::vector<T>;

public:
    inline List() = default;

    inline List(typename base::size_type count)
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
