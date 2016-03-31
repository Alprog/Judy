
#include "Model.h"

using base = Node;

Model::Model()
{
    mesh = CreateCubeMesh();
    renderState = new RenderState();
}

void Model::Render(Matrix matrix, Renderer* renderer)
{
    renderer->Draw(mesh, matrix, renderState);
    base::Render(matrix, renderer);
}
