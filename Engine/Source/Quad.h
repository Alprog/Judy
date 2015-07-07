
#pragma once

#include "Node.h"
#include "string"
#include "Transform.h"
#include "Meta/TypeMeta.h"

#define __Meta__

class __Meta__ Quad : public Node
{
    friend class TypeMeta<Quad>;

public:
    Quad();

    virtual void Update(double delta) override;
    virtual void Render(Renderer* renderer) override;

    Vector2 Size;
    Transform Transform;

    std::string Shader;
    std::string Texture;
};
