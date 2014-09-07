
#include "Quad.h"
#include "Renderer.h"

using base = Node;

Quad::Quad()
    : base()
    , Size({1, 1})
{
}

void Quad::Update(double delta)
{
    base::Update(delta);
}

void Quad::Render(Renderer* renderer)
{
    renderer->DrawQuad(this);

    base::Render(renderer);
}
