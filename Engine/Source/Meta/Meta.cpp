
#include "Meta.h"
#include "TypeMeta.h"

#include "ClassDefiner.h"

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

//Node* node = (Node*)TypeMeta<Node>::Instance()->constructors[1]->Invoke({1});

/*
//void (B::*p)(int) = &B::test;
std::string::iterator (std::string::*p)() = &std::string::begin;
std::string::size_type (std::string::*p2)(char, std::string::size_type) const = &std::string::find;
//std::string::size_type (std::string::*p3)(char, std::string::size_type) = p2;
auto pp = static_cast<std::string::size_type (std::string::*)(char, std::string::size_type) const>(&std::string::find);
ClassDefiner<std::string>()
    .method("begin", static_cast<std::string::iterator (std::string::*)()>(&std::string::begin))
    .method("clear", &std::string::clear)
    .method("find", pp)
;
ClassDefiner<B>()
    .method("test", static_cast<int (B::*)(char) const>(&B::test))
;
B b;
std::vector<Any> args { &b, 8 };
auto result = TypeMeta<B>::Instance()->methods[0]->Invoke(args);
printf("%i \n", result.as<int>());

std::string* str = new std::string("123456");
std::vector<Any> args2 { str, '3', 0ull };
auto r2 = TypeMeta<std::string>::Instance()->methods[2]->Invoke(args2);
printf("%i\n", r2.as<std::string::size_type>());

//bool a = ITypeMeta::Get<int>()->isPointer();
//bool b = ITypeMeta::Get<int*>()->isPointer();
//bool c = ITypeMeta::Get<int>()->PointerType()->isPointer();
//TypeMeta<int>::Instance()->name = "int";
*/

