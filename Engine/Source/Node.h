
#pragma once

#include <vector>
#include "Math/Vector2.h"
#include "Math/Transform.h"
#include "Meta/ITypeMeta.h"
#include "Attributes.h"
#include "SmartPointer.h"
#include "Scriptable.h"

class Renderer;

class _(Meta)__ Node : public Scriptable
{
    friend class Meta;

public:
    Node();
    Node(int a);
    virtual ~Node();

    Node* Parent();
    int ChildCount();
    Node* Child(int i);

    void AddChild(Node* node);
    void RemoveChild(Node* node);
    void Unparent();
    void Reparent(Node* parent);

    void Update(double delta);
    virtual void UpdateHelper(double delta);

    virtual void Render(Matrix matrix, Renderer* renderer);

    _(Serialize, Inspect)__ Transform transform;

private:
    Node* parent;
    _(Serialize)__ List<SmartPointer<Node>> childs;
};
