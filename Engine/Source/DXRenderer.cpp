
#include "DXRenderer.h"

#include <wrl.h>

using namespace Microsoft::WRL;

DXRenderer::DXRenderer()
{
    ComPtr<ID3D12Debug> debugController;
    if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController))))
    {
        debugController->EnableDebugLayer();
    }
}

void DXRenderer::Clear(Color color)
{

}

void DXRenderer::Draw(Mesh* mesh, Matrix matrix, RenderState* renderState)
{

}

void DXRenderer::DrawQuad(Quad* quad)
{

}

void DXRenderer::Render(Node* scene, RenderTarget* renderTarget)
{

}
