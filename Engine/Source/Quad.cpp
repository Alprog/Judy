
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

void Quad::Render(Matrix matrix, Renderer* renderer)
{
    renderer->DrawQuad(this);
    base::Render(matrix, renderer);
}
