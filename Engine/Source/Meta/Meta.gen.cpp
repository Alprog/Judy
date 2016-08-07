
#include "Meta.h"
#include "TypeMeta.h"
#include "ClassDefiner.h"
#include "List.h"
#include "Map.h"
#include "Set.h"
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
#include "Object.h"
#include "Quad.h"
#include "Window.h"
#include "Render/RendererFrontend.h"

template <typename T>
void Meta::DefineList()
{
    using type = List<T>;

    ClassDefiner<type>(this, "List<T>")
        .template templateArgument<T>()
        .template base<std::vector<T>>()
        .constructor()
        .template constructor<size_t>()
        .template constructor<std::initializer_list<T>>()
        .method("at", &type::at)
        .method("add", &type::add)
        .function("serialize", &type::serialize)
        .function("deserialize", &type::deserialize)
    ;
}

template <typename T1, typename T2>
void Meta::DefineMap()
{
    using type = Map<T1, T2>;
    ClassDefiner<type>(this, "Map<T1, T2>")
        .template templateArgument<T1>()
        .template templateArgument<T2>()
        .template base<std::unordered_map<T1, T2>>()
        .constructor()
        .function("serialize", &type::serialize)
        .function("deserialize", &type::deserialize)
    ;
}

template <typename T>
void Meta::DefineSet()
{
    using type = Set<T>;
    ClassDefiner<type>(this, "Set<T>")
        .template templateArgument<T>()
        .template base<std::unordered_set<T>>()
        .constructor()
        .template constructor<List<T>>().attr("Serialize")
        .method("toList", &type::toList).attr("Serialize")
    ;
}

void Meta::DefineClasses()
{
    DefineList<CallInfo>();
    DefineSet<int>();
    DefineList<float>();
    DefineSet<Window*>();
    DefineList<Ref<Node>>();
    DefineList<int>();
    DefineList<Window*>();

    ClassDefiner<CallInfo>(this, "CallInfo")
        .constructor()
        .constructor<std::string, std::string, int, int, int>()
        .field("name", &CallInfo::name).attr("Serialize")
        .field("source", &CallInfo::source).attr("Serialize")
        .field("line", &CallInfo::line).attr("Serialize")
        .field("startLine", &CallInfo::startLine).attr("Serialize")
        .field("endLine", &CallInfo::endLine).attr("Serialize")
    ;

    ClassDefiner<CallStack>(this, "CallStack")
        .constructor()
        .field("calls", &CallStack::calls).attr("Serialize")
    ;

    ClassDefiner<DebugCommand>(this, "DebugCommand")
        .constructor()
        .constructor<std::string>()
        .field("name", &DebugCommand::name).attr("Serialize")
    ;

    ClassDefiner<FileBreakpoints>(this, "FileBreakpoints")
        .constructor()
        .constructor<std::string, Set<int>>()
        .field("fileName", &FileBreakpoints::fileName).attr("Serialize")
        .field("lines", &FileBreakpoints::lines).attr("Serialize")
    ;

    ClassDefiner<LogMessage>(this, "LogMessage")
        .constructor()
        .constructor<std::string>()
        .field("text", &LogMessage::text).attr("Serialize")
    ;

    ClassDefiner<Quaternion>(this, "Quaternion")
        .constructor<float, float, float, float>()
        .constructor<List<float>>().attr("Serialize")
        .method("toList", &Quaternion::toList).attr("Serialize")
        .function("YawPitchRoll", &Quaternion::YawPitchRoll)
        .field("x", &Quaternion::x).attr("Bind")
        .field("y", &Quaternion::y).attr("Bind")
        .field("z", &Quaternion::z).attr("Bind")
        .field("w", &Quaternion::w).attr("Bind")
    ;

    ClassDefiner<Transform>(this, "Transform")
        .constructor()
        .method("getMatrix", &Transform::getMatrix)
        .property("translation").attr("Bind").attr("Inspect")
            .getter("getTranslation", &Transform::getTranslation)
            .setter("setTranslation", &Transform::setTranslation)
        .property("rotation").attr("Bind").attr("Inspect")
            .getter("getRotation", &Transform::getRotation)
            .setter("setRotation", &Transform::setRotation)
        .property("scaling").attr("Bind").attr("Inspect")
            .getter("getScaling", &Transform::getScaling)
            .setter("setScaling", &Transform::setScaling)
        .field("translation", &Transform::translation).attr("Serialize")
        .field("rotation", &Transform::rotation).attr("Serialize")
        .field("scaling", &Transform::scaling).attr("Serialize")
        .field("invalidateMatrix", &Transform::invalidateMatrix)
        .field("matrix", &Transform::matrix)
    ;

    ClassDefiner<Vector2>(this, "Vector2")
        .constructor()
        .constructor<float, float>()
        .constructor<List<float>>().attr("Serialize")
        .method("toList", &Vector2::toList).attr("Serialize")
        .method("Length", &Vector2::Length)
        .method("SquaredLength", &Vector2::SquaredLength)
        .field("x", &Vector2::x).attr("Bind").attr("Inspect")
        .field("y", &Vector2::y).attr("Bind").attr("Inspect")
    ;

    ClassDefiner<Vector3>(this, "Vector3")
        .constructor<float, float, float>()
        .constructor<List<float>>().attr("Serialize")
        .method("toList", &Vector3::toList).attr("Serialize")
        .method("Length", &Vector3::Length)
        .method("SquaredLength", &Vector3::SquaredLength)
        .field("x", &Vector3::x).attr("Bind").attr("Inspect")
        .field("y", &Vector3::y).attr("Bind").attr("Inspect")
        .field("z", &Vector3::z).attr("Bind").attr("Inspect")
    ;

    ClassDefiner<Vector4>(this, "Vector4")
        .constructor<float, float, float, float>()
        .constructor<List<float>>()
        .method("toList", &Vector4::toList).attr("Serialize")
        .method("Length", &Vector4::Length)
        .method("SquaredLength", &Vector4::SquaredLength)
        .field("x", &Vector4::x).attr("Bind").attr("Inspect")
        .field("y", &Vector4::y).attr("Bind").attr("Inspect")
        .field("z", &Vector4::z).attr("Bind").attr("Inspect")
        .field("w", &Vector4::w).attr("Bind").attr("Inspect")
    ;

    ClassDefiner<App>(this, "App")
        .base<Object>()
        .constructor()
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
        .base<Node>()
        .constructor()
        .field("mesh", &Model::mesh)
        .field("renderState", &Model::renderState)
        .field("name", &Model::name).attr("Serialize").attr("Inspect")
    ;

    ClassDefiner<Node>(this, "Node")
        .base<Object>()
        .constructor()
        .constructor<int>()
        .constructor()
        .method("Parent", &Node::Parent)
        .method("ChildCount", &Node::ChildCount)
        .method("Child", &Node::Child)
        .method("AddChild", &Node::AddChild)
        .method("RemoveChild", &Node::RemoveChild)
        .method("Unparent", &Node::Unparent)
        .method("Reparent", &Node::Reparent)
        .method("Update", &Node::UpdateHelper)
        .method("Render", &Node::Render)
        .field("transform", &Node::transform).attr("Serialize").attr("Inspect")
        .field("parent", &Node::parent)
        .field("childs", &Node::childs).attr("Serialize")
    ;

    /*ClassDefiner<Object>(this, "Object")
        .constructor()
        .constructor()
        .method("Retain", &Object::Retain)
        .method("Release", &Object::Release)
        .function("GC", &Object::GC)
        .field("referenceCount", &Object::referenceCount)
        .field("luaObject", &Object::luaObject)
        .field("luaClass", &Object::luaClass).attr("Serialize")
    ;*/

    ClassDefiner<Quad>(this, "Quad")
        .base<Node>()
        .constructor()
        .method("Render", &Quad::Render)
        .field("Size", &Quad::Size).attr("Serialize").attr("Inspect")
        .field("Shader", &Quad::Shader).attr("Serialize").attr("Inspect")
        .field("Texture", &Quad::Texture).attr("Serialize").attr("Inspect")
    ;

    ClassDefiner<Window>(this, "Window")
        .base<Object>()
        .function("Create", &Window::Create)
        .method("show", &Window::show)
        .method("ProcessEvents", &Window::ProcessEvents)
        .method("Update", &Window::Update)
        .method("Render", &Window::Render)
        .field("scene", &Window::scene).attr("Bind")
        .field("renderTarget", &Window::renderTarget).attr("Bind")
        .field("renderer", &Window::renderer).attr("Bind")
    ;
}

