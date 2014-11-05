
#pragma once

#include <vector>
#include "Math/Vector2.h"
#include "Meta/TypeMeta.h"

class Renderer;

class Node
{
    friend TypeMeta<Node>;

public:
    Node();

    Node* Parent();
    size_t ChildCount();
    Node* Child(int i);

    void AddChild(Node* node);
    void RemoveChild(Node* node);
    void Unparent();
    void Reparent(Node* parent);

    virtual void Update(double delta);
    virtual void Render(Renderer* renderer);

private:
    Node* parent;
    std::vector<Node*> childs;
};
