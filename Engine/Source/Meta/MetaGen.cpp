
#include "Meta.h"

#include "ClassDefiner.h"
#include "TypeMeta.h"

#include "App.h"
#include "Node.h"
#include "Quad.h"

#include <functional>

class A
{
public:
    virtual int test(char a) const { return 7 + a; }
};

class B : public A
{
public:
    virtual int test(char a) const override { return 5 + a; }
    int test(float a) { return 88; }
};

Meta::Meta()
{
    DefineBuildInType<bool>("bool");
    DefineBuildInType<int>("int");
    DefineBuildInType<float>("float");
    DefineBuildInType<std::string>("string");

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

    ClassDefiner<TestStruct>()
        .constructor()
        .field("a", &TestStruct::a)
        .field("b", &TestStruct::b)
        .field("d", &TestStruct::d)
        .field("g", &TestStruct::g)
    ;

    ClassDefiner<SubStruct>()
        .constructor()
        .field("e", &SubStruct::e)
    ;

    ClassDefiner<App>()
        .method("StartMainLoop", &App::StartMainLoop)
    ;

    ClassDefiner<Node>()
        .constructor()
        .constructor<int>()
        .method("Update", &Node::Update)
        //.method("Render", &Node::Render)
        .method("ChildCount", &Node::ChildCount)
        .method("RemoveChild", &Node::RemoveChild)
        .method("AddChild", &Node::AddChild)
    ;

    ClassDefiner<Quad>()
        .constructor()
        .method("Update", &Quad::Update)
        //.method("Render", &Quad::Render)
    ;

    //Node* node = (Node*)TypeMeta<Node>::Instance()->constructors[1]->Invoke({1});

    int i = TypeMeta<Node>::Instance()->methods[1]->GetArgCount();

    i = i + 1;
}

