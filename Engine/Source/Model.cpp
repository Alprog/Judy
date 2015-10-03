
#include "Model.h"

using base = Node;

Model::Model()
{
    mesh = CreateCubeMesh();
    material = new Material();
}

void Model::Update(double delta)
{
}

void Model::Render(Matrix matrix, Renderer* renderer)
{
    renderer->Draw(mesh, material, matrix);
    base::Render(matrix, renderer);
}
