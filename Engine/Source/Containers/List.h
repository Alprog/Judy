
#pragma once

#include <vector>

#define __Meta__

template <typename T>
__Meta__ class List : public std::vector<T>
{
    using base = std::vector<T>;

    inline T& at(int index) { return base::at(index); }
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
