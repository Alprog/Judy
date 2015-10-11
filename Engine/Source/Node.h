
#pragma once

#include <vector>
#include "Math/Vector2.h"
#include "Math/Transform.h"
#include "Meta/TypeMeta.h"
#include "Attributes.h"

class Renderer;

class _(Meta)__ Node
{
    friend class Meta;

public:
    Node();
    Node(int a);

    Node* Parent();
    int ChildCount();
    Node* Child(int i);

    void AddChild(Node* node);
    void RemoveChild(Node* node);
    void Unparent();
    void Reparent(Node* parent);

    virtual void Update(double delta);
    virtual void Render(Matrix matrix, Renderer* renderer);

    _(Serialize)__ Transform transform;

private:
    Node* parent;
    _(Serialize)__ List<Node*> childs;
};
