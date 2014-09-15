
#pragma once

#include "Node.h"
#include "string"
#include "Transform.h"

#define META(_)
#define SERIALIZED

class Quad : public Node
{

public:
    Quad();

    virtual void Update(double delta) override;
    virtual void Render(Renderer* renderer) override;

    SERIALIZED Vector2 Size;
    SERIALIZED Transform Transform;

    SERIALIZED std::string Shader;
    SERIALIZED std::string Texture;
};
