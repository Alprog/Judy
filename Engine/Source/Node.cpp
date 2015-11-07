
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

Node::~Node()
{
    printf("delete\n");
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
    return childs[i].Get();
}

void Node::AddChild(Node* node)
{
    node->Unparent();
    Ref<Node> ref(node);
    childs.push_back(std::move(ref));
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
    for (auto& child : childs)
    {
        child->Update(delta);
    }
}

void Node::Render(Matrix matrix, Renderer* renderer)
{
    for (auto& child : childs)
    {
        auto& childMatrix = child->transform.getMatrix();
        child->Render(childMatrix * matrix, renderer);
    }
}
