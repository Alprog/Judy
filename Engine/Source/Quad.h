
#pragma once

#include "Node.h"
#include "string"
#include "Math/Transform2D.h"
#include "Meta/TypeMeta.h"

#define __Meta__
#define __Serialize__

class __Meta__ Quad : public Node
{
    friend class Meta;

public:
    Quad();

    virtual void Update(double delta) override;
    virtual void Render(Matrix matrix, Renderer* renderer) override;

    __Serialize__ Vector2 Size;
    __Serialize__ std::string Shader;
    __Serialize__ std::string Texture;
};
