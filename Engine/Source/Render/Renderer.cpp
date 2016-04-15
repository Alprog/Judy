
#include "Renderer.h"
#include "RendererFrontend.h"
#include "Node.h"

void Renderer::Render(Node* scene, RenderTarget* target)
{
    RendererFrontend frontEnd;
    scene->Render(scene->transform.getMatrix(), &frontEnd);
    this->Render(frontEnd.commands, target);
}
