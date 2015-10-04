
#include "Meta.h"
#include "TypeMeta.h"
#include "ClassDefiner.h"
#include "List.h"
#include "CallInfo.h"
#include "CallStack.h"
#include "DebugCommand.h"
#include "FileBreakpoints.h"
#include "LogMessage.h"
#include "Quaternion.h"
#include "Transform.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "App.h"
#include "Model.h"
#include "Node.h"
#include "Quad.h"
#include "Renderer.h"
#include "Window.h"

void Meta::regClasses()
{
    ClassDefiner<CallInfo>(this, "CallInfo")
        .constructor()
        .constructor<std::string, std::string, int, int, int>()
        .field("name", &CallInfo::name)
        .field("source", &CallInfo::source)
        .field("line", &CallInfo::line)
        .field("startLine", &CallInfo::startLine)
        .field("endLine", &CallInfo::endLine)
    ;

    ClassDefiner<CallStack>(this, "CallStack")
        .constructor()
        .field("calls", &CallStack::calls)
    ;

    ClassDefiner<DebugCommand>(this, "DebugCommand")
        .constructor()
        .constructor<std::string>()
        .field("name", &DebugCommand::name)
    ;

    ClassDefiner<FileBreakpoints>(this, "FileBreakpoints")
        .constructor()
        .constructor<std::string, std::unordered_set<int>>()
        .field("fileName", &FileBreakpoints::fileName)
        .field("lines", &FileBreakpoints::lines)
    ;

    ClassDefiner<LogMessage>(this, "LogMessage")
        .constructor()
        .constructor<std::string>()
        .field("text", &LogMessage::text)
    ;

    ClassDefiner<Quaternion>(this, "Quaternion")
        .constructor<float, float, float, float>()
        .function("YawPitchRoll", &Quaternion::YawPitchRoll)
        .field("x", &Quaternion::x)
        .field("y", &Quaternion::y)
        .field("z", &Quaternion::z)
        .field("w", &Quaternion::w)
    ;

    ClassDefiner<Transform>(this, "Transform")
        .constructor()
        .method("getTranslation", &Transform::getTranslation)
        .method("getRotation", &Transform::getRotation)
        .method("getScaling", &Transform::getScaling)
        .method("setTranslation", &Transform::setTranslation)
        .method("setRotation", &Transform::setRotation)
        .method("setScaling", &Transform::setScaling)
        .method("getMatrix", &Transform::getMatrix)
        .field("translation", &Transform::translation)
        .field("rotation", &Transform::rotation)
        .field("scaling", &Transform::scaling)
        .field("invalidateMatrix", &Transform::invalidateMatrix)
        .field("matrix", &Transform::matrix)
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
        .field("arr", &SubStruct::arr)
        .field("set", &SubStruct::set)
        .field("map", &SubStruct::map)
    ;

    ClassDefiner<TestStruct>(this, "TestStruct")
        .constructor<float, int, char*, SubStruct>()
        .constructor()
        .field("a", &TestStruct::a)
        .field("c", &TestStruct::c)
        .field("d", &TestStruct::d)
        .field("dd", &TestStruct::dd)
        .field("g", &TestStruct::g)
        .field("arr", &TestStruct::arr)
        .field("map", &TestStruct::map)
        .field("b", &TestStruct::b)
    ;

    ClassDefiner<App>(this, "App")
        .function("Instance", &App::Instance)
        .method("StartMainLoop", &App::StartMainLoop)
        .method("AddWindow", &App::AddWindow)
        .method("RemoveWindow", &App::RemoveWindow)
        .method("UpdateCollection", &App::UpdateCollection)
        .field("Windows", &App::Windows)
        .field("AddedWindows", &App::AddedWindows)
        .field("RemovedWindows", &App::RemovedWindows)
    ;

    ClassDefiner<Model>(this, "Model")
        .constructor()
        .method("Update", &Model::Update)
        .method("Render", &Model::Render)
        .field("mesh", &Model::mesh)
        .field("material", &Model::material)
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
        .field("transform", &Node::transform)
        //.field("parent", &Node::parent)
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
        .method("Draw", &Renderer::Draw)
        .method("Render", &Renderer::Render)
        .method("Clear", &Renderer::Clear)
    ;

    ClassDefiner<WindowM>(this, "WindowM")
        .function("Create", &WindowM::Create)
        .method("show", &WindowM::show)
        .method("ProcessEvents", &WindowM::ProcessEvents)
        .method("Update", &WindowM::Update)
        .method("Render", &WindowM::Render)
    ;
}
