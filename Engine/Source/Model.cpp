
#include "Model.h"

#include "TextureManager.h"
#include "ShaderManager.h"
#include "Render/ConstantBuffer.h"

using base = Node;

Model::Model()
{
    mesh = CreateCubeMesh();
    renderState = new RenderState();

    renderState->vertexShader = ShaderManager::Instance()->GetShader("shadersTextured", Shader::Type::Vertex);
    renderState->pixelShader = ShaderManager::Instance()->GetShader("shadersTextured", Shader::Type::Pixel);
    renderState->texture = TextureManager::Instance()->GetTexture("test.png");

    renderState->constantBuffer = new ConstantBuffer();

    renderState->link();
}

#include "Render/DX/DXConstantBufferImpl.h"

void Model::Render(Matrix matrix, Renderer* renderer)
{
    auto impl = renderState->constantBuffer->dxImpl;
    impl->data.MVP = matrix * Matrix::RotationX(3.1416) * Matrix::OrthographicLH(2, 2, -2, 2);
    impl->Update();

    renderer->Draw(mesh, matrix, renderState);
    base::Render(matrix, renderer);
}
