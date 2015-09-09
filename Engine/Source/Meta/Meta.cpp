
#include "Meta.h"
#include "TypeMeta.h"

#include "ClassDefiner.h"

template <typename T>
std::vector<Any> toAnyVector(T& arr)
{
    std::vector<Any> result(arr.size());
    int i = 0;
    for (auto& element : arr)
    {
        result[i++] = element;
    }
    return result;
}

template <typename T>
std::vector<T> anyVectorToVector(std::vector<Any>& vector)
{
    std::vector<T> result;
    for (auto& element : vector)
    {
        result.push_back(element);
    }
    return result;
}

template <typename T>
std::unordered_set<T> anyVectorToSet(std::vector<Any>& vector)
{
    std::unordered_set<T> result;
    for (auto& element : vector)
    {
        result.insert(element.as<T>());
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
        .function("fromAnyVector", &anyVectorToVector<T>)
        .method("size", &VT::size)
        .method("at", at)
        .method("push_back", push_back)
    ;
}

template <typename T>
void Meta::regSet()
{
    using ST = std::unordered_set<T>;

    auto name = TypeMetaOf<T>()->name;
    name = "unordered_set<" + name + ">";

    ClassDefiner<ST>(this, name.c_str())
        .valueType<T>()
        .constructor()
        .function("toAnyVector", &toAnyVector<ST>)
        .function("fromAnyVector", &anyVectorToSet<T>)
        .method("size", &ST::size)
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
    regSet<int>();

    regClasses();
}
