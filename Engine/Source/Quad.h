
#pragma once

#include "Node.h"
#include "string"
#include "Math/Transform2D.h"
#include "Meta/ITypeMeta.h"
#include "Attributes.h"

class [[Meta]] Quad : public Node
{
    friend class Meta;

public:
    Quad();

    virtual void render(Matrix matrix, RendererFrontend* renderer) override;

    [[Serialize, Inspect]] Vector2 size;
    [[Serialize, Inspect]] std::string shader;
    [[Serialize, Inspect]] std::string texture;
};
