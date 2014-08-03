
#pragma once

#include <vector>

class Node
{
public:
    Node();

    Node* Parent();
    size_t ChildCount();
    Node* Child(int i);

    void AddChild(Node* node);
    void RemoveChild(Node* node);
    void Unparent();
    void Reparent(Node* parent);

    void Update(double delta);
    void Render();

private:
    Node* parent;
    std::vector<Node*> childs;
};
