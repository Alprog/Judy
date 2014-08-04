
#pragma once

#include "Node.h"

class Quad : public Node
{

public:
    Quad();

    virtual void Update(double delta) override;
    virtual void Render(Renderer* renderer) override;
};
