
#pragma once

#include "Node.h"
#include "string"
#include "Vector2.h"

class Quad : public Node
{

public:
    Quad();

    virtual void Update(double delta) override;
    virtual void Render(Renderer* renderer) override;

    Vector2 Size;


    std::wstring Shader;
    std::wstring Texture;
};
