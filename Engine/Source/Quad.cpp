
#include "Quad.h"
#include "Render/IRenderer.h"

using base = Node;

Quad::Quad()
    : base()
    , size(1, 1)
{
}

void Quad::Render(Matrix matrix, RendererFrontend* renderer)
{
    base::Render(matrix, renderer);
}
