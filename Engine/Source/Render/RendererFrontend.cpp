
#include "RendererFrontend.h"
#include "Render/ConstantBuffer.h"

void RendererFrontend::render(Node* scene)
{
    Context context;
    context.View = Matrix::Identity; //Matrix::RotationX(3.1416);
    context.Projection = Matrix::OrthographicLH(2, 2, -2, 2);
    context.ViewProjection = context.View * context.Projection;
    contexts.push(context);


    scene->render(scene->transform.getMatrix(), this);

}

#if WINDOWS
#include "Render/DX/DXConstantBufferImpl.h"
#include "RenderManager.h"
#include "Render/DX/DXRenderer.h"
#endif

void RendererFrontend::draw(Mesh* mesh, Matrix matrix, RenderState* renderState)
{
    RenderCommand command;
    command.mesh = mesh;
    command.state = renderState;

    command.state->constantBuffer->data.MVP = matrix * contexts.back().ViewProjection;

#if WINDOWS
    DXRenderer* renderer = (DXRenderer*)RenderManager::getInstance()->renderers[0];
    renderer->getImpl(command.state->constantBuffer)->update();
#endif

    commands.push_back(command);
}
