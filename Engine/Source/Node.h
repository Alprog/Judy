
#pragma once

#include <vector>
#include "Math/Vector2.h"
#include "Math/Transform.h"
#include "Meta/ITypeMeta.h"
#include "Attributes.h"
#include "Ref.h"
#include "Object.h"

class Renderer;

class _(Meta)__ Node : public Object
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

    void Update(float delta);
    virtual void UpdateHelper(float delta);

    virtual void Render(Matrix matrix, Renderer* renderer);

    _(Serialize, Inspect)__ Transform transform;

private:
    Node* parent;
    _(Serialize)__ List<Ref<Node>> childs;
};
