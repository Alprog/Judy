
#include "Quad.h"
#include "Render/Renderer.h"

using base = Node;

Quad::Quad()
    : base()
    , Size(1, 1)
{
}

void Quad::Render(Matrix matrix, Renderer* renderer)
{
    renderer->DrawQuad(this);
    base::Render(matrix, renderer);
}
