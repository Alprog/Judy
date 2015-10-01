
#pragma once

#include "Node.h"
#include "string"
#include "Math/Transform2D.h"
#include "Meta/TypeMeta.h"

#define __Meta__

class __Meta__ Quad : public Node
{
    friend class Meta;

public:
    Quad();

    virtual void Update(double delta) override;
    virtual void Render(Renderer* renderer) override;

    Vector2 Size;
    Transform2D Transform;

    std::string Shader;
    std::string Texture;
};
