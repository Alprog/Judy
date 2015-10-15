
#include "Node.h"
#include <algorithm>

#include "LuaMachine.h"

Node::Node()
    : parent {nullptr}
{
}

Node::Node(int i)
    : parent {nullptr}
{
}

Node* Node::Parent()
{
    return parent;
}

int Node::ChildCount()
{
    return childs.size();
}

Node* Node::Child(int i)
{
    return childs[i];
}

void Node::AddChild(Node* node)
{
    node->Unparent();
    childs.push_back(node);
    node->parent = this;
}

void Node::RemoveChild(Node* node)
{
    auto position = find(begin(childs), end(childs), node);
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

void Node::Update(double delta)
{
//    if (LuaObject != nullptr)
//    {
//        auto L = LuaMachine::Instance()->L;

//        lua_push(L, )

//    }
}

void Node::UpdateHelper(double delta)
{
    for (auto child : childs)
    {
        child->Update(delta);
    }
}

void Node::Render(Matrix matrix, Renderer* renderer)
{
    for (auto child : childs)
    {
        auto& childMatrix = child->transform.getMatrix();
        child->Render(childMatrix * matrix, renderer);
    }
}

std::string Node::getLuaClass()
{
    throw std::runtime_error("not imlement");
}

void Node::setLuaClass(std::string name)
{
    printf("lua class: %s\n", name.c_str());
    fflush(stdout);
}
