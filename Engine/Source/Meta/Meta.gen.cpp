
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
    ;

    ClassDefiner<Vector2>(this, "Vector2")
        .constructor()
        .constructor<float, float>()
        .method("Length", &Vector2::Length)
        .method("SquaredLength", &Vector2::SquaredLength)
    ;

    ClassDefiner<Vector3>(this, "Vector3")
        .constructor<float, float, float>()
        .method("Length", &Vector3::Length)
        .method("SquaredLength", &Vector3::SquaredLength)
    ;

    ClassDefiner<Vector4>(this, "Vector4")
        .constructor<float, float, float, float>()
        .method("Length", &Vector4::Length)
        .method("SquaredLength", &Vector4::SquaredLength)
    ;

    ClassDefiner<SubStruct>(this, "SubStruct")
        .constructor()
        .constructor<int>()
    ;

    ClassDefiner<TestStruct>(this, "TestStruct")
        .constructor<float, int, char *, SubStruct>()
        .constructor()
    ;

    ClassDefiner<App>(this, "App")
        .method("StartMainLoop", &App::StartMainLoop)
        .method("AddWindow", &App::AddWindow)
        .method("RemoveWindow", &App::RemoveWindow)
        .method("UpdateCollection", &App::UpdateCollection)
    ;

    ClassDefiner<Node>(this, "Node")
        .constructor()
        .constructor<int>()
        .method("Parent", &Node::Parent)
        .method("ChildCount", &Node::ChildCount)
        .method("Child", &Node::Child)
        .method("AddChild", &Node::AddChild)
        .method("RemoveChild", &Node::RemoveChild)
        .method("Unparent", &Node::Unparent)
        .method("Reparent", &Node::Reparent)
        .method("Update", &Node::Update)
        .method("Render", &Node::Render)
    ;

    ClassDefiner<Quad>(this, "Quad")
        .constructor()
        .method("Update", &Quad::Update)
        .method("Render", &Quad::Render)
    ;

    ClassDefiner<Renderer>(this, "Renderer")
        .method("DrawQuad", &Renderer::DrawQuad)
        .method("Render", &Renderer::Render)
        .method("Clear", &Renderer::Clear)
    ;
}
