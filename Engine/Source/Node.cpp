
#include "Node.h"
#include <algorithm>

#include "LuaMachine.h"

Node::Node()
    : parent {nullptr}
{
}

Node::Node(int /*i*/)
    : parent {nullptr}
{
}

Node::~Node()
{
}

Node* Node::Parent()
{
    return parent;
}

int Node::ChildCount()
{
    return (int)childs.size();
}

Node* Node::Child(int i)
{
    return childs[i].Get();
}

void Node::AddChild(Node* node)
{
    node->Unparent();
    childs.push_back(Ref<Node>(node));
    node->parent = this;
}

void Node::RemoveChild(Node* node)
{
    auto position = find_if(begin(childs), end(childs), [&](Ref<Node> const& ref)
    {
        return ref.Get() == node;
    });

    if (position != end(childs))
    {
        childs.erase(position);
        node->parent = nullptr;
    }
}

void Node::Unparent()
{
    if (parent != nullptr)
    {
        parent->RemoveChild(this);
    }
}

void Node::Reparent(Node* parent)
{
    if (this->parent != nullptr)
    {
        this->parent->RemoveChild(this);
    }
    if (parent != nullptr)
    {
        parent->AddChild(this);
    }
}

#include "luainc.h"

void Node::Update(float delta)
{
    if (luaObject == nullptr)
    {
        UpdateHelper(delta);
    }
    else
    {
        auto L = LuaMachine::Instance()->getL();
        lua_pushuserdata(L, luaObject); // U
        lua_getfield(L, -1, "Update"); // UF
        lua_insert(L, -2); // FU
        lua_pushnumber(L, delta); // FUV
        lua_call(L, 2, 0); //
    }
}

void Node::UpdateHelper(float delta)
{
    for (auto& child : childs)
    {
        child->Update(delta);
    }
}

void Node::Render(Matrix matrix, RendererFrontend* renderer)
{
    for (auto& child : childs)
    {
        auto const& childMatrix = child->transform.getMatrix();
        child->Render(childMatrix * matrix, renderer);
    }
}
