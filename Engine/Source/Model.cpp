
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

void Model::Render(Matrix matrix, Renderer* renderer)
{
    renderer->Draw(mesh, matrix, renderState);
    base::Render(matrix, renderer);
}
