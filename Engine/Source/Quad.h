
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

    virtual void Render(Matrix matrix, Renderer* renderer) override;

    [[Serialize]] [[Inspect]] Vector2 Size;
    [[Serialize]] [[Inspect]] std::string Shader;
    [[Serialize]] [[Inspect]] std::string Texture;
};
