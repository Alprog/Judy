
#include "Meta.h"
#include "TypeMeta.h"

#include "ClassDefiner.h"
#include "CallInfo.h"
#include "Node.h"

template <typename T>
std::vector<Any> toAnyVector(T& in)
{
    std::vector<Any> out(in.size());
    int i = 0;
    for (auto& element : in)
    {
        out[i++] = element;
    }
    return out;
}

template <typename T1, typename T2>
std::vector<Any> mapToAnyVector(std::unordered_map<T1, T2>& in)
{
    std::vector<Any> out(in.size() * 2);
    int i = 0;
    for (auto& pair : in)
    {
        out[i++] = pair.first;
        out[i++] = pair.second;
    }
    return out;
}

template <typename T>
std::vector<T> anyVectorToVector(std::vector<Any>& in)
{
    std::vector<T> result;
    for (auto& element : in)
    {
        result.push_back(element);
    }
    return result;
}

template <typename T>
std::unordered_set<T> anyVectorToSet(std::vector<Any>& in)
{
    std::unordered_set<T> result;
    for (auto& element : in)
    {
        result.insert(element.as<T>());
    }
    return result;
}

template <typename T1, typename T2>
std::unordered_map<T1, T2> anyVectorToMap(std::vector<Any>& in)
{
    std::unordered_map<T1, T2> out;
    for (int i = 0; i < in.size(); i += 2)
    {
        auto key = in[i].as<T1>();
        auto value = in[i + 1].as<T2>();
        out[key] = value;
    }
    return out;
}

template <typename T1, typename T2>
void Meta::regMap()
{
    using MT = std::unordered_map<T1, T2>;

    auto name1 = TypeMetaOf<T1>()->name;
    auto name2 = TypeMetaOf<T2>()->name;
    auto name = "unordered_map<" + name1 + ", " + name2 + ">";

    ClassDefiner<MT>(this, name.c_str())
        .template valueType<T2>()
        .constructor()
        .function("toAnyVector", &mapToAnyVector<T1, T2>)
        .function("fromAnyVector", &anyVectorToMap<T1, T2>)
        .method("size", &MT::size)
    ;
}

Meta::Meta()
{
    DefineBuildInType<bool>("bool");
    DefineBuildInType<int>("int");
    DefineBuildInType<float>("float");
    DefineBuildInType<std::string>("string");
    DefineBuildInType<char>("char");
    DefineBuildInType<double>("double");

    DefineClasses();
}
