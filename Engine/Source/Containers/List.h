
#pragma once

#include <vector>
#include "Meta/Any.h"
#include "Meta/Serializer.h"

#define __Meta__
#define __Serialize__

template <typename T>
__Meta__ class List : public std::vector<T>
{
    friend class Meta;
    using base = std::vector<T>;

public:
    inline List() = default;

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

    static Any deserialize(Serializer* serializer)
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


//auto at = static_cast<typename VT::reference (VT::*)(typename VT::size_type)>(&VT::at);
//auto push_back = static_cast<void (VT::*)(const typename VT::value_type&)>(&VT::push_back);

//ClassDefiner<VT> a = ClassDefiner<VT>(this, name.c_str())
//    .template valueType<T>()
//    .constructor()
//    .function("toAnyVector", &toAnyVector<VT>)
//    .function("fromAnyVector", &anyVectorToVector<T>)
//    .method("size", &VT::size)
//    .method("at", at)
//    .method("push_back", push_back)
//;
