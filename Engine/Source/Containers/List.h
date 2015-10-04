
#pragma once

#include <vector>
#include "Meta/Any.h"

#define __Meta__
#define __Serialize__

template <typename T>
__Meta__ class List : public std::vector<T>
{
    using base = std::vector<T>;

public:
    inline List() = default;

    inline List(std::initializer_list<T> items)
        : base(items)
    {
    }

    inline T& at(int index) { return base::at(index); }

private:
    __Serialize__ List<Any> toList()
    {
        List<Any> out(size());
        for (auto i = 0; i < size(); i++)
        {
            out[i++] = this->at(i);
        }
        return out;
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
