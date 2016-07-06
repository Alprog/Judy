
#include "IRenderer.h"
#include "RendererFrontend.h"
#include "Node.h"

void IRenderer::Render(Node* scene, RenderTarget* target)
{
    RendererFrontend frontEnd;
    frontEnd.Render(scene);

    this->Render(frontEnd.commands, target);
}
