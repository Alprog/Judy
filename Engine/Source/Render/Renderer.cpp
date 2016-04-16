
#include "Renderer.h"
#include "RendererFrontend.h"
#include "Node.h"

void Renderer::Render(Node* scene, RenderTarget* target)
{
    RendererFrontend frontEnd;
    frontEnd.Render(scene);

    this->Render(frontEnd.commands, target);
}
