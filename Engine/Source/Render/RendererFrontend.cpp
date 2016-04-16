
#include "RendererFrontend.h"
#include "Render/ConstantBuffer.h"

void RendererFrontend::Render(Node* scene)
{
    Context context;
    context.View = Matrix::RotationX(3.1416);
    context.Projection = Matrix::OrthographicLH(2, 2, -2, 2);
    context.ViewProjection = context.View * context.Projection;
    contexts.push(context);


    scene->Render(scene->transform.getMatrix(), this);

}

#include "Render/DX/DXConstantBufferImpl.h"

void RendererFrontend::Draw(Mesh* mesh, Matrix matrix, RenderState* renderState)
{
    RenderCommand command;
    command.mesh = mesh;
    command.state = renderState;

    command.state->constantBuffer->data.MVP = matrix * contexts.back().ViewProjection;
    command.state->constantBuffer->dxImpl->Update();

    commands.push_back(command);
}
