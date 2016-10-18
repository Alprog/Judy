
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

Node* Node::getParent()
{
    return parent;
}

int Node::childCount()
{
    return childs.size();
}

Node* Node::child(int i)
{
    return childs[i].get();
}

void Node::addChild(Node* node)
{
    node->unparent();
    childs.push_back(Ref<Node>(node));
    node->parent = this;
}

void Node::removeChild(Node* node)
{
    auto position = find_if(begin(childs), end(childs), [&](Ref<Node> const& ref)
    {
        return ref.get() == node;
    });

    if (position != end(childs))
    {
        childs.erase(position);
        node->parent = nullptr;
    }
}

void Node::unparent()
{
    if (parent != nullptr)
    {
        parent->removeChild(this);
    }
}

void Node::reparent(Node* parent)
{
    if (this->parent != nullptr)
    {
        this->parent->removeChild(this);
    }
    if (parent != nullptr)
    {
        parent->addChild(this);
    }
}

#include "luainc.h"

void Node::update(float delta)
{
    if (luaObject == nullptr)
    {
        updateHelper(delta);
    }
    else
    {
        auto L = LuaMachine::instance()->getL();
        lua_pushuserdata(L, luaObject); // U
        lua_getfield(L, -1, "update"); // UF
        lua_insert(L, -2); // FU
        lua_pushnumber(L, delta); // FUV
        lua_call(L, 2, 0); //
    }
}

void Node::updateHelper(float delta)
{
    for (auto& child : childs)
    {
        child->update(delta);
    }
}

void Node::render(Matrix matrix, RendererFrontend* renderer)
{
    for (auto& child : childs)
    {
        auto const& childMatrix = child->transform.getMatrix();
        child->render(childMatrix * matrix, renderer);
    }
}
