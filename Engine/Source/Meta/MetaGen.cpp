
#include "Meta.h"

#include "MetaDefiner.h"
#include "TypeMeta.h"

#include "App.h"
#include "Node.h"

Meta::Meta()
{
    bool a = TypeMeta<int>::Instance()->isPointer();
    bool b = TypeMeta<int*>::Instance()->isPointer();

    //TypeMeta<int>::Instance()->name = "int";

    MetaDefiner<TestStruct>("TestStruct")
        .constructor()
        .field("a", &TestStruct::a)
        .field("b", &TestStruct::b)
        .field("c", &TestStruct::c)
        .field("d", &TestStruct::d)
    ;

    MetaDefiner<SubStruct>("SubStruct")
        .constructor()
        .field("e", &SubStruct::e)
     ;

    MetaDefiner<App>("App")
        .method("StartMainLoop", &App::StartMainLoop)
    ;

    MetaDefiner<Node>("Node")
        .constructor()
        .constructor<int>()
        .method("ChildCount", &Node::ChildCount)
        .method("RemoveChild", &Node::RemoveChild)
        .method("AddChild", &Node::AddChild)
    ;

    //Node* node = (Node*)TypeMeta<Node>::Instance()->constructors[1]->Invoke({1});

    int i = TypeMeta<Node>::Instance()->methods[1]->GetArgCount();

    i = i + 1;
}

