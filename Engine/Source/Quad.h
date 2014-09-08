
#pragma once

#include "Node.h"
#include "string"
#include "Transform.h"

class Quad : public Node
{

public:
    Quad();

    virtual void Update(double delta) override;
    virtual void Render(Renderer* renderer) override;

    Vector2 Size;
    Transform Transform;

    std::string Shader;
    std::string Texture;
};
