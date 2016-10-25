
#include "IRenderer.h"
#include "RendererFrontend.h"
#include "Node.h"

void IRenderer::render(Node* scene, RenderTarget* target)
{
    RendererFrontend frontEnd;
    frontEnd.render(scene);

    target->onRendering(getType());
    this->render(frontEnd.commands, target);
}
