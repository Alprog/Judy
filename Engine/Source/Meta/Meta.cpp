
#include "Meta.h"
#include "TypeMeta.h"

#include "ClassDefiner.h"

template <typename T>
std::vector<Any> toAnyVector(T& arr)
{
    std::vector<Any> result(arr.size());
    for (auto i = 0; i < arr.size(); i++)
    {
        result[i] = arr[i];
    }
    return result;
}

template <typename T>
T anyVectorToVector(std::vector<Any>& vector)
{
    T result;
    for (auto& element : vector)
    {
        result.push_back(element);
    }
    return result;
}

template <typename T>
void Meta::regVector()
{
    using VT = std::vector<T>;

    auto name = TypeMetaOf<T>()->name;
    name = "vector<" + name + ">";

    auto at = static_cast<VT::reference (VT::*)(VT::size_type)>(&VT::at);
    auto push_back = static_cast<void (VT::*)(const VT::value_type&)>(&VT::push_back);

    ClassDefiner<VT>(this, name.c_str())
        .valueType<T>()
        .constructor()
        .function("toAnyVector", &toAnyVector<VT>)
        .function("fromAnyVector", &anyVectorToVector<VT>)
        .method("size", &VT::size)
        .method("at", at)
        .method("push_back", push_back)
    ;
}

Meta::Meta()
{
    DefineBuildInType<bool>("bool");
    DefineBuildInType<int>("int");
    DefineBuildInType<float>("float");
    DefineBuildInType<std::string>("string");
    DefineBuildInType<char>("char");

    regVector<int>();

    regClasses();
}
