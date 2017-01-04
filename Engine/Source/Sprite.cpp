
#include "Sprite.h"

#include <ShaderManager.h>
#include <TextureManager.h>
#include <ConstantBuffer.h>
#include <RendererFrontend.h>

using base = Node;

Sprite::Sprite()
{
    mesh = createQuadMesh();
    renderState = new RenderState();

    renderState->constantBuffer = new ConstantBuffer();

    renderState->setVertexShader(ShaderManager::getInstance()->getShader("Shaders/test", "vsmain"));
    renderState->setPixelShader(ShaderManager::getInstance()->getShader("Shaders/test", "psmain"));
    renderState->texture = TextureManager::getInstance()->getTexture("judy.png");
}

void Sprite::render(Matrix matrix, RendererFrontend* renderer)
{
    renderer->draw(mesh, matrix, renderState);
    base::render(matrix, renderer);
}

Path Sprite::getImagePath() const
{
    return imagePath;
}

void Sprite::setImagePath(Path path)
{
    this->imagePath = path;
}
