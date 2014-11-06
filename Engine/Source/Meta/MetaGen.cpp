
#include "Meta.h"

#include "MetaDefiner.h"
#include "TypeMeta.h"

#include "App.h"
#include "Node.h"

Meta::Meta()
{
    TypeMeta<int>::Instance()->name = "int";

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

    MetaDefiner<Node>("Node")
        .constructor()
        .method("ChildCount", &Node::ChildCount)
        .method("RemoveChild", &Node::RemoveChild)
    ;


    int i = TypeMeta<Node>::Instance()->methods[1]->GetArgCount();

    i = i + 1;
}

