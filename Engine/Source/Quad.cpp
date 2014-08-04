
#include "Quad.h"

using base = Node;

Quad::Quad()
    : base()
{

}

void Quad::Update(double delta)
{
    base::Update(delta);
}

void Quad::Render(Renderer* renderer)
{
    base::Render(renderer);
}
