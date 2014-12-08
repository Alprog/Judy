
#include "Meta.h"

#include "ClassDefiner.h"
#include "TypeMeta.h"

#include "App.h"
#include "Node.h"

Meta::Meta()
{
    bool a = ITypeMeta::Get<int>()->isPointer();
    bool b = ITypeMeta::Get<int*>()->isPointer();

    //bool c = ITypeMeta::Get<int>()->PointerType()->isPointer();
    //TypeMeta<int>::Instance()->name = "int";

    ClassDefiner<TestStruct>("TestStruct")
        //.constructor()
        .field("a", &TestStruct::a)
        .field("b", &TestStruct::b)
        //.field("c", &TestStruct::c)
        .field("d", &TestStruct::d)
        //.field("dd", &TestStruct::dd)
        .field("g", &TestStruct::g)
        //.field("arr", &TestStruct::arr)
    ;

    ClassDefiner<SubStruct>("SubStruct")
        //.constructor()
        .field("e", &SubStruct::e)
     ;

    ClassDefiner<App>("App")
        .method("StartMainLoop", &App::StartMainLoop)
    ;

    ClassDefiner<Node>("Node")
        //.constructor()
        .constructor<int>()
        .method("ChildCount", &Node::ChildCount)
        .method("RemoveChild", &Node::RemoveChild)
        .method("AddChild", &Node::AddChild)
    ;

    //Node* node = (Node*)TypeMeta<Node>::Instance()->constructors[1]->Invoke({1});

    int i = TypeMeta<Node>::Instance()->methods[1]->GetArgCount();

    i = i + 1;
}

