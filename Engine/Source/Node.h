
#pragma once

#include <vector>
#include "Math/Vector2.h"
#include "Math/Transform.h"
#include "Meta/ITypeMeta.h"
#include "Attributes.h"
#include "Ref.h"
#include "Object.h"

class RendererFrontend;

class [[Meta]] Node : public Object
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

    virtual void Render(Matrix matrix, RendererFrontend* renderer);

    [[Serialize]] [[Inspect]] Transform transform;

private:
    Node* parent;
    [[Serialize]] List<Ref<Node>> childs;
};
