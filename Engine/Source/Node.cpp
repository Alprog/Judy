#include "Node.h"

Node::Node()
    : parent {nullptr}
{
}

Node* Node::Parent()
{
    return parent;
}

size_t Node::ChildCount()
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
    for (auto child : childs)
    {
        child->Update(delta);
    }
}

void Node::Render()
{
    for (auto child : childs)
    {
        child->Render();
    }
}
