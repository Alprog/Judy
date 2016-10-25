
#include "Meta.h"
#include "TypeMeta.h"
#include "ClassDefiner.h"
#include "List.h"
#include "Map.h"
#include "Set.h"
#include "InputDevice.h"
#include "InputSystem.h"
#include "VirtualDevice.h"
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
#include <RendererFrontend.h>

template <typename T>
void Meta::defineList()
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
void Meta::defineMap()
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
void Meta::defineSet()
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

void Meta::defineClasses()
{
    defineList<CallInfo>();
    defineSet<int>();
    defineList<float>();
    defineSet<Window*>();
    defineList<Ref<Node>>();
    defineList<int>();
    defineList<Window*>();

    ClassDefiner<InputDevice>(this, "InputDevice")
        .method("updateState", &InputDevice::updateState)
        .method("isPressed", &InputDevice::isPressed)
        .method("isReleased", &InputDevice::isReleased)
        .method("wasPressed", &InputDevice::wasPressed)
        .method("wasReleased", &InputDevice::wasReleased)
        .method("onPressed", &InputDevice::onPressed)
        .method("onReleased", &InputDevice::onReleased)
        .field("type", &InputDevice::type)
        .field("currentState", &InputDevice::currentState)
        .field("previousState", &InputDevice::previousState)
    ;

    ClassDefiner<InputSystem>(this, "InputSystem")
        .base<Object>()
        .function("getInstance", &InputSystem::getInstance)
        .method("updateState", &InputSystem::updateState)
        .field("devices", &InputSystem::devices)
        .method("isPressed", &InputSystem::isPressed)
        .method("onPressed", &InputSystem::onPressed)
    ;

    ClassDefiner<VirtualDevice>(this, "VirtualDevice")
        .base<Object>()
        .constructor()
        .method("addKeySource", &VirtualDevice::addKeySource).attr("Bind")
        .method("isPressed", &VirtualDevice::isPressed).attr("Bind")
        .method("isReleased", &VirtualDevice::isReleased).attr("Bind")
        .method("wasPressed", &VirtualDevice::wasPressed).attr("Bind")
        .method("wasReleased", &VirtualDevice::wasReleased).attr("Bind")
        .method("onPressed", &VirtualDevice::onPressed).attr("Bind")
        .method("onReleased", &VirtualDevice::onReleased).attr("Bind")
        .field("keys", &VirtualDevice::keys)
    ;

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
        .function("yawPitchRoll", &Quaternion::yawPitchRoll)
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
        .method("length", &Vector2::length)
        .method("squaredLength", &Vector2::squaredLength)
        .field("x", &Vector2::x).attr("Bind").attr("Inspect")
        .field("y", &Vector2::y).attr("Bind").attr("Inspect")
    ;

    ClassDefiner<Vector3>(this, "Vector3")
        .constructor<float, float, float>()
        .constructor<List<float>>().attr("Serialize")
        .method("toList", &Vector3::toList).attr("Serialize")
        .method("length", &Vector3::length)
        .method("squaredLength", &Vector3::squaredLength)
        .field("x", &Vector3::x).attr("Bind").attr("Inspect")
        .field("y", &Vector3::y).attr("Bind").attr("Inspect")
        .field("z", &Vector3::z).attr("Bind").attr("Inspect")
    ;

    ClassDefiner<Vector4>(this, "Vector4")
        .constructor<float, float, float, float>()
        .constructor<List<float>>()
        .method("toList", &Vector4::toList).attr("Serialize")
        .method("length", &Vector4::length)
        .method("squaredLength", &Vector4::squaredLength)
        .field("x", &Vector4::x).attr("Bind").attr("Inspect")
        .field("y", &Vector4::y).attr("Bind").attr("Inspect")
        .field("z", &Vector4::z).attr("Bind").attr("Inspect")
        .field("w", &Vector4::w).attr("Bind").attr("Inspect")
    ;

    ClassDefiner<App>(this, "App")
        .base<Object>()
        .constructor()
        .function("getInstance", &App::getInstance)
        .method("startMainLoop", &App::startMainLoop)
        .method("addWindow", &App::addWindow)
        .method("removeWindow", &App::removeWindow)
        .method("updateCollection", &App::updateCollection)
        .field("windows", &App::windows)
        .field("addedWindows", &App::addedWindows)
        .field("removedWindows", &App::removedWindows)
    ;

    ClassDefiner<Model>(this, "Model")
        .base<Node>()
        .constructor()
        .method("render", &Model::render)
        .field("mesh", &Model::mesh)
        .field("renderState", &Model::renderState)
        .field("name", &Model::name).attr("Serialize").attr("Inspect")
    ;

    ClassDefiner<Node>(this, "Node")
        .base<Object>()
        .constructor()
        .constructor<int>()
        .constructor()
        .method("getParent", &Node::getParent)
        .method("childCount", &Node::childCount)
        .method("getChild", &Node::getChild)
        .method("addChild", &Node::addChild)
        .method("removeChild", &Node::removeChild)
        .method("unparent", &Node::unparent)
        .method("reparent", &Node::reparent)
        .method("update", &Node::updateInternal)
        .method("render", &Node::render)
        .method("getTransform", &Node::getTransform)
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
        .method("render", &Quad::render)
        .field("size", &Quad::size).attr("Serialize").attr("Inspect")
        .field("shader", &Quad::shader).attr("Serialize").attr("Inspect")
        .field("texture", &Quad::texture).attr("Serialize").attr("Inspect")
    ;

    ClassDefiner<Window>(this, "Window")
        .base<Object>()
        .function("create", &Window::create)
        .method("show", &Window::show)
        .method("processEvents", &Window::processEvents)
        .method("update", &Window::update)
        .method("render", &Window::render)
        .method("switchRenderType", &Window::switchRenderType)
        .field("scene", &Window::scene).attr("Bind")
        .field("renderTarget", &Window::renderTarget).attr("Bind")
        .field("renderer", &Window::renderer).attr("Bind")
    ;
}

