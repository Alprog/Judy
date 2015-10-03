
#include "Model.h"

using base = Node;

Model::Model()
{
    mesh = CreateCubeMesh();
    material = new Material();
}

void Model::Update(double delta)
{
    static float a = 0;
    a += 0.003f;

    auto rotation = Quaternion::YawPitchRoll(a / 2, a, a / 2);
    transform.setRotation(rotation);
}

void Model::Render(Matrix matrix, Renderer* renderer)
{
    renderer->Draw(mesh, material, matrix);
    base::Render(matrix, renderer);
}
