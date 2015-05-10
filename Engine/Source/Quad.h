
#pragma once

#include "Node.h"
#include "string"
#include "Transform.h"
#include "Meta/TypeMeta.h"

class Quad : public Node
{
    friend TypeMeta<Quad>;

public:
    Quad();

    virtual void Update(double delta) override;
    virtual void Render(Renderer* renderer) override;

    Vector2 Size;
    Transform Transform;

    std::string Shader;
    std::string Texture;
};
