
#include "Meta.h"
#include "TypeMeta.h"
#include "ClassDefiner.h"
#include "Transform.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "App.h"
#include "Node.h"
#include "Quad.h"
#include "Renderer.h"

void Meta::regClasses()
{
    ClassDefiner<Transform>(this, "Transform")
        .constructor()
        .method("GetMatrix", &Transform::GetMatrix)
        .field("Pivot", &Transform::Pivot)
        .field("Translation", &Transform::Translation)
        .field("Rotation", &Transform::Rotation)
        .field("Scaling", &Transform::Scaling)
    ;

    ClassDefiner<Vector2>(this, "Vector2")
        .constructor()
        .constructor<float, float>()
        .method("Length", &Vector2::Length)
        .method("SquaredLength", &Vector2::SquaredLength)
        .field("x", &Vector2::x)
        .field("y", &Vector2::y)
    ;

    ClassDefiner<Vector3>(this, "Vector3")
        .constructor<float, float, float>()
        .method("Length", &Vector3::Length)
        .method("SquaredLength", &Vector3::SquaredLength)
        .field("x", &Vector3::x)
        .field("y", &Vector3::y)
        .field("z", &Vector3::z)
    ;

    ClassDefiner<Vector4>(this, "Vector4")
        .constructor<float, float, float, float>()
        .method("Length", &Vector4::Length)
        .method("SquaredLength", &Vector4::SquaredLength)
        .field("x", &Vector4::x)
        .field("y", &Vector4::y)
        .field("z", &Vector4::z)
        .field("w", &Vector4::w)
    ;

    ClassDefiner<SubStruct>(this, "SubStruct")
        .constructor()
        .constructor<int>()
        .field("e", &SubStruct::e)
    ;

    ClassDefiner<TestStruct>(this, "TestStruct")
        .constructor<float, int, char *, SubStruct>()
        .constructor()
        .field("a", &TestStruct::a)
        .field("c", &TestStruct::c)
        .field("d", &TestStruct::d)
        .field("dd", &TestStruct::dd)
        .field("g", &TestStruct::g)
        .field("arr", &TestStruct::arr)
        .field("b", &TestStruct::b)
    ;

    ClassDefiner<App>(this, "App")
        .method("StartMainLoop", &App::StartMainLoop)
        .method("AddWindow", &App::AddWindow)
        .method("RemoveWindow", &App::RemoveWindow)
        .method("UpdateCollection", &App::UpdateCollection)
        .field("Windows", &App::Windows)
        .field("AddedWindows", &App::AddedWindows)
        .field("RemovedWindows", &App::RemovedWindows)
    ;

    ClassDefiner<Node>(this, "Node")
        .constructor()
        .constructor<int>()
        .method("Parent", &Node::Parent)
        .method("ChildCount", &Node::ChildCount)
        //.method("Child", &Node::Child)
        .method("AddChild", &Node::AddChild)
        .method("RemoveChild", &Node::RemoveChild)
        .method("Unparent", &Node::Unparent)
        .method("Reparent", &Node::Reparent)
        .method("Update", &Node::Update)
        .method("Render", &Node::Render)
        .field("parent", &Node::parent)
        .field("childs", &Node::childs)
    ;

    ClassDefiner<Quad>(this, "Quad")
        .constructor()
        .method("Update", &Quad::Update)
        .method("Render", &Quad::Render)
        .field("Size", &Quad::Size)
        .field("Transform", &Quad::Transform)
        .field("Shader", &Quad::Shader)
        .field("Texture", &Quad::Texture)
    ;

    ClassDefiner<Renderer>(this, "Renderer")
        .method("DrawQuad", &Renderer::DrawQuad)
        .method("Render", &Renderer::Render)
        .method("Clear", &Renderer::Clear)
    ;
}
