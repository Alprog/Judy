
#include "RendererFrontend.h"

void RendererFrontend::Draw(Mesh* mesh, Matrix matrix, RenderState* renderState)
{
    RenderCommand command;
    command.mesh = mesh;
    command.state = renderState;
    commands.push_back(command);
}
