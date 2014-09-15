
#include "DXRenderer.h"

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

#include "Matrix.h"

#include <DXGI1_2.h>

#include <stdio.h>
#include <iostream>

#include "DXSwapChain.h"
#include "Win/WinRenderTarget.h"

#include "Images.h"

#include "Node.h"

ID3D11Buffer* quadVertexBuffer;
ID3D11Buffer* quadIndexBuffer;
ID3D11Buffer* constantBuffer;
bool quadInited = false;

struct ConstantBufferType
{
    Matrix WVP;
    Matrix M1;
    Matrix M2;
};


struct VertexType
{
    Vector3 position;
    Vector4 color;
    Vector2 uv;
};


DXRenderer::DXRenderer()
{
    auto type = D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_HARDWARE;
    auto featureLevels = D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_11_0;
    D3D_FEATURE_LEVEL featureLevel;
    D3D11CreateDevice(NULL, type, NULL, 0, &featureLevels, 1, D3D11_SDK_VERSION, &device, &featureLevel, &deviceContext);
}

void DXRenderer::Clear(Color color)
{
    ID3D11RenderTargetView* rtView;
    ID3D11DepthStencilView* dsView;
    deviceContext->OMGetRenderTargets(1, &rtView, &dsView);
    deviceContext->ClearRenderTargetView(rtView, color.data);
}

void DXRenderer::SetTexture(std::string name)
{
    auto view = (ID3D11ShaderResourceView*)textures[name];
    if (view == nullptr)
    {
        Image* image = Images::LoadPng(name);

        ID3D11Texture2D* texture;
        D3D11_TEXTURE2D_DESC desc;
        desc.Width = image->width;
        desc.Height = image->height;
        desc.MipLevels = 1;
        desc.ArraySize = 1;
        desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        desc.SampleDesc = DXGI_SAMPLE_DESC {1, 0};
        desc.Usage = D3D11_USAGE_DEFAULT;
        desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
        desc.CPUAccessFlags = 0;
        desc.MiscFlags = 0;

        D3D11_SUBRESOURCE_DATA data;
        data.pSysMem = image->data;
        data.SysMemPitch = image->width * 4;
        data.SysMemSlicePitch = 0;

        device->CreateTexture2D(&desc, &data, &texture);
        device->CreateShaderResourceView(texture, NULL, &view);

        textures[name] = view;
    }
    deviceContext->PSSetShaderResources(0, 1, &view);
}

void DXRenderer::SetShader(std::string name)
{
    auto shader = shaders[name];
    if (shader == nullptr)
    {
        std::wstring wname(begin(name), end(name));
        shader = new DXShaderResource(device, wname);
        shaders[name] = shader;
    }
    deviceContext->IASetInputLayout(shader->inputLayout);
    deviceContext->VSSetShader(shader->vertexShader, NULL, 0);
    deviceContext->PSSetShader(shader->pixelShader, NULL, 0);

}

DXSwapChain* DXRenderer::GetSwapChain(RenderTarget* renderTarget)
{
    auto swapChain = swapChains[renderTarget];
    if (swapChain == nullptr)
    {
        swapChain = new DXSwapChain(this, renderTarget);
        swapChains[renderTarget] = swapChain;
    }
    return swapChain;
}

void DXRenderer::InitQuad()
{
    D3D11_BUFFER_DESC vertexBufferDesc;
    vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
    vertexBufferDesc.ByteWidth = sizeof(VertexType) * 6;
    vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    vertexBufferDesc.MiscFlags = 0;
    vertexBufferDesc.StructureByteStride = 0;

    device->CreateBuffer(&vertexBufferDesc, NULL, &quadVertexBuffer);

    //-----------

    D3D11_BUFFER_DESC indexBufferDesc;
    indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    indexBufferDesc.ByteWidth = sizeof(unsigned int) * 6;
    indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    indexBufferDesc.CPUAccessFlags = 0;
    indexBufferDesc.MiscFlags = 0;
    indexBufferDesc.StructureByteStride = 0;

    unsigned int indices[6] = {0, 1, 2, 2, 1, 3};

    D3D11_SUBRESOURCE_DATA indexData;
    indexData.pSysMem = indices;
    indexData.SysMemPitch = 0;
    indexData.SysMemSlicePitch = 0;

    device->CreateBuffer(&indexBufferDesc, &indexData, &quadIndexBuffer);

    //-----------

    D3D11_BUFFER_DESC constantBufferDesc;
    constantBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
    constantBufferDesc.ByteWidth = sizeof(ConstantBufferType);
    constantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    constantBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    constantBufferDesc.MiscFlags = 0;
    constantBufferDesc.StructureByteStride = 0;

    device->CreateBuffer(&constantBufferDesc, NULL, &constantBuffer);

    //-----------

    quadInited = true;
}

void DXRenderer::DrawQuad(Quad* quad)
{
    if (!quadInited) InitQuad();

    auto x = quad->Size.x;
    auto y = quad->Size.y;

    VertexType vertices[4];
    vertices[0].position = {-x, y, 0.0f};
    vertices[1].position = {x, y, 0.0f};
    vertices[2].position = {-x, -y, 0.0f};
    vertices[3].position = {x, -y, 0.0f};

    vertices[0].uv = {0.0f, 0.0f};
    vertices[1].uv = {1.0f, 0.0f};
    vertices[2].uv = {0.0f, 1.0f};
    vertices[3].uv = {1.0f, 1.0f};

    vertices[0].color = {1.0f, 0.0f, 0.0f, 1.0f};
    vertices[1].color = {0.0f, 1.0f, 0.0f, 1.0f};
    vertices[2].color = {0.0f, 0.0f, 1.0f, 1.0f};
    vertices[3].color = {0.0f, 0.0f, 1.0f, 1.0f};

    D3D11_MAPPED_SUBRESOURCE resource;
    deviceContext->Map(quadVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &resource);
    memcpy(resource.pData, &vertices[0], sizeof(VertexType) * 4);
    deviceContext->Unmap(quadVertexBuffer, 0);

    deviceContext->Map(constantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &resource);
    auto buffer = (ConstantBufferType*)resource.pData;
    buffer->WVP = Matrix::Identity;

    buffer->M1 = quad->Transform.GetMatrix();
    buffer->M2 = Matrix::Identity;

    deviceContext->Unmap(constantBuffer, 0);


    unsigned int stride = sizeof(VertexType);
    unsigned int offset = 0;
    deviceContext->IASetVertexBuffers(0, 1, &quadVertexBuffer, &stride, &offset);
    deviceContext->IASetIndexBuffer(quadIndexBuffer, DXGI_FORMAT::DXGI_FORMAT_R32_UINT, 0);
    deviceContext->VSSetConstantBuffers(0, 1, &constantBuffer);

    SetShader(quad->Shader);
    SetTexture(quad->Texture);

    deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    deviceContext->DrawIndexed(6, 0, 0);
}

bool a = false;

void DXRenderer::Render(Node* scene, RenderTarget* renderTarget)
{
    auto swapChain = GetSwapChain(renderTarget);
    deviceContext->OMSetRenderTargets(1, &swapChain->view, NULL);

    if (a == false)
    {
        D3D11_VIEWPORT viewport;
        viewport.TopLeftX = 0;
        viewport.TopLeftY = 0;
        viewport.Width = 800;
        viewport.Height = 800;
        viewport.MinDepth = 0.0f;
        viewport.MaxDepth = 1.0f;
        deviceContext->RSSetViewports(1, &viewport);

        D3D11_RECT rect;
        rect.left = 0;
        rect.top = 0;
        rect.right = 400;
        rect.bottom = 800;
        deviceContext->RSSetScissorRects(1, &rect);

        D3D11_RASTERIZER_DESC rsdesc;
        rsdesc.FillMode = D3D11_FILL_SOLID;
        rsdesc.CullMode = D3D11_CULL_NONE;
        rsdesc.FrontCounterClockwise = true;
        rsdesc.DepthBias = false;
        rsdesc.DepthBiasClamp = 0;
        rsdesc.SlopeScaledDepthBias = 0;
        rsdesc.DepthClipEnable = false;
        rsdesc.ScissorEnable = true;
        rsdesc.MultisampleEnable = false;
        rsdesc.AntialiasedLineEnable = false;

        ID3D11RasterizerState* rsstate;
        a = device->CreateRasterizerState(&rsdesc, &rsstate);
        printf("%X", a); fflush(stdout);

        deviceContext->RSSetState(rsstate);

        a = true;
    }

    Clear({ 0.0f, 0.0f, 1.0f, 1.0f });

    ID3D11SamplerState* state;

    D3D11_SAMPLER_DESC samplerDesc;
    samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
    samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDesc.MipLODBias = 0;
    samplerDesc.MaxAnisotropy = 16;
    samplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
    samplerDesc.BorderColor[0] = 0;
    samplerDesc.BorderColor[1] = 0;
    samplerDesc.BorderColor[2] = 0;
    samplerDesc.BorderColor[3] = 0;
    samplerDesc.MinLOD = 0;
    samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;


    device->CreateSamplerState(&samplerDesc, &state);
    deviceContext->PSSetSamplers(0, 1, &state);

    scene->Render(this);

    swapChain->swapChain->Present(1, 0);

}

/*static int a = 0; a++;
if (a == 100)
{
    swapChain->SetFullscreenState(true, NULL);

    view->Release();
    backBuffer->Release();
    swapChain->ResizeBuffers(2, 1366, 768, DXGI_FORMAT_UNKNOWN, 0);
    swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBuffer);
    device->CreateRenderTargetView(backBuffer, NULL, &view);
}
if (a == 1000)
{
    swapChain->SetFullscreenState(false, NULL);

    view->Release();
    backBuffer->Release();
    swapChain->ResizeBuffers(2, 400, 800, DXGI_FORMAT_UNKNOWN, 0);
    swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBuffer);
    device->CreateRenderTargetView(backBuffer, NULL, &view);
}*/
