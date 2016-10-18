
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

    Node* getParent();
    int childCount();
    Node* child(int i);

    void addChild(Node* node);
    void removeChild(Node* node);
    void unparent();
    void reparent(Node* parent);

    void update(float delta);
    virtual void updateHelper(float delta);

    virtual void render(Matrix matrix, RendererFrontend* renderer);

    [[Serialize]] [[Inspect]] Transform transform;

private:
    Node* parent;
    [[Serialize]] List<Ref<Node>> childs;
};
