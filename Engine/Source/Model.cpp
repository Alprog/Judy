
#include "Model.h"

#include "TextureManager.h"
#include "ShaderManager.h"
#include "Render/ConstantBuffer.h"
#include "Render/PipelineState.h"
#include "Render/RendererFrontend.h"

using base = Node;

Model::Model()
{
    mesh = createCubeMesh();
    renderState = new RenderState();

    renderState->constantBuffer = new ConstantBuffer();

    renderState->setVertexShader(ShaderManager::getInstance()->getShader("Shaders/test", "vsmain"));
    renderState->setPixelShader(ShaderManager::getInstance()->getShader("Shaders/test", "psmain"));
    renderState->texture = TextureManager::getInstance()->getTexture("skullbox.png");
}

void Model::render(Matrix matrix, RendererFrontend* renderer)
{
    renderer->draw(mesh, matrix, renderState);
    base::render(matrix, renderer);
}
