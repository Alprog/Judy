
#include "DXRenderer.h"

#include "Vector.h"
#include "Matrix.h"

#include <DXGI1_2.h>
#include <d3dcompiler.h>

#include <stdio.h>
#include <iostream>

#include "DXSwapChain.h"
#include "Win/WinRenderTarget.h"

#include "Images.h"

ID3D11VertexShader* vs;
ID3D11PixelShader* ps;
ID3D11InputLayout* layout;
ID3D11Buffer* vertexBuffer;
ID3D11Buffer* constantBuffer;

struct ConstantBufferType
{
    Matrix world;
    Matrix view;
    Matrix projection;
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

}

void DXRenderer::SetTexture(std::wstring name)
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

/*void DXRenderer::SetVertexShader(std::wstring name)
{
    auto vs = (ID3D11VertexShader*)vertexShaders[name];
    if (vs == nullptr)
    {
        ID3DBlob* vscode;
        ID3DBlob* message;
        D3DCompileFromFile(name, NULL, NULL, "ColorVertexShader", "vs_5_0", 0, 0, &vscode, &message);
        device->CreateVertexShader(vscode->GetBufferPointer(), vscode->GetBufferSize(), NULL, &vs);
    }
}*/

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

bool a = false;

void DXRenderer::Render(Scene* scene, RenderTarget* renderTarget)
{
    auto swapChain = GetSwapChain(renderTarget);
    deviceContext->OMSetRenderTargets(1, &swapChain->view, NULL);


    if (a == false)
    {
        a = true;

        auto vsfile = L"Shaders\\color.vs";
        auto psfile = L"Shaders\\color.ps";

        ID3DBlob* vscode;
        ID3DBlob* pscode;
        ID3DBlob* message = nullptr;

        HRESULT a;

        auto flags = D3DCOMPILE_ENABLE_BACKWARDS_COMPATIBILITY;

        a = D3DCompileFromFile(vsfile, NULL, NULL, "ColorVertexShader", "vs_5_0", flags, 0, &vscode, &message);
        printf("VS:%X;", a); fflush(stdout);
        a = D3DCompileFromFile(psfile, NULL, NULL, "ColorPixelShader", "ps_5_0", flags, 0, &pscode, &message);
        printf("PS:%X;", a); fflush(stdout);

        a = device->CreateVertexShader(vscode->GetBufferPointer(), vscode->GetBufferSize(), NULL, &vs);
        printf("VS:%X; ", a); fflush(stdout);
        a = device->CreatePixelShader(pscode->GetBufferPointer(), pscode->GetBufferSize(), NULL, &ps);
        printf("PS:%X;", a); fflush(stdout);

        D3D11_INPUT_ELEMENT_DESC element_desc[3];
        element_desc[0].SemanticName = "POSITION";
        element_desc[0].SemanticIndex = 0;
        element_desc[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
        element_desc[0].InputSlot = 0;
        element_desc[0].AlignedByteOffset = 0;
        element_desc[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
        element_desc[0].InstanceDataStepRate = 0;

        element_desc[1].SemanticName = "COLOR";
        element_desc[1].SemanticIndex = 0;
        element_desc[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
        element_desc[1].InputSlot = 0;
        element_desc[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
        element_desc[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
        element_desc[1].InstanceDataStepRate = 0;

        element_desc[2].SemanticName = "TEXCOORD";
        element_desc[2].SemanticIndex = 0;
        element_desc[2].Format = DXGI_FORMAT_R32G32_FLOAT;
        element_desc[2].InputSlot = 0;
        element_desc[2].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
        element_desc[2].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
        element_desc[2].InstanceDataStepRate = 0;

        a = device->CreateInputLayout(element_desc, 3, vscode->GetBufferPointer(), vscode->GetBufferSize(), &layout);
        printf("%X", a); fflush(stdout);

        VertexType vertices[6];
        vertices[0].position = {-0.8f, 0.8f, 0.0f};
        vertices[1].position = {0.8f, 0.8f, 0.0f};
        vertices[2].position = {-0.8f, -0.8f, 0.0f};
        vertices[3].position = {-0.8f, -0.8f, 0.0f};
        vertices[4].position = {0.8f, 0.8f, 0.0f};
        vertices[5].position = {0.8f, -0.8f, 0.0f};

        vertices[0].uv = {0.0f, 0.0f};
        vertices[1].uv = {1.0f, 0.0f};
        vertices[2].uv = {0.0f, 1.0f};
        vertices[3].uv = {0.0f, 1.0f};
        vertices[4].uv = {1.0f, 0.0f};
        vertices[5].uv = {1.0f, 1.0f};

        vertices[0].color = {1.0f, 0.0f, 0.0f, 1.0f};
        vertices[1].color = {0.0f, 1.0f, 0.0f, 1.0f};
        vertices[2].color = {0.0f, 0.0f, 1.0f, 1.0f};
        vertices[3].color = {1.0f, 0.0f, 0.0f, 1.0f};
        vertices[4].color = {0.0f, 1.0f, 0.0f, 1.0f};
        vertices[5].color = {0.0f, 0.0f, 1.0f, 1.0f};

        D3D11_SUBRESOURCE_DATA vertexData;
        vertexData.pSysMem = vertices;
        vertexData.SysMemPitch = 0;
        vertexData.SysMemSlicePitch = 0;

        D3D11_BUFFER_DESC vertexBufferDesc;
        vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
        vertexBufferDesc.ByteWidth = sizeof(VertexType) * 6;
        vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
        vertexBufferDesc.CPUAccessFlags = 0;
        vertexBufferDesc.MiscFlags = 0;
        vertexBufferDesc.StructureByteStride = 0;

        a = device->CreateBuffer(&vertexBufferDesc, &vertexData, &vertexBuffer);
        printf("%X", a); fflush(stdout);

        D3D11_BUFFER_DESC constantBufferDesc;
        constantBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
        constantBufferDesc.ByteWidth = sizeof(ConstantBufferType);
        constantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
        constantBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
        constantBufferDesc.MiscFlags = 0;
        constantBufferDesc.StructureByteStride = 0;

        a = device->CreateBuffer(&constantBufferDesc, NULL, &constantBuffer);
        printf("%X", a); fflush(stdout);

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

        //SetFocus(hWnd);
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

    Color color { 0.0f, 0.0f, 1.0f, 1.0f };
    //Clear(color);
    deviceContext->ClearRenderTargetView(swapChain->view, color.data);

    unsigned int stride = sizeof(VertexType);
    unsigned int offset = 0;

    deviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
    //deviceContext->VSSetConstantBuffers(0, 1, &constantBuffer);
    //deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

    deviceContext->IASetInputLayout(layout);
    deviceContext->VSSetShader(vs, NULL, 0);
    deviceContext->PSSetShader(ps, NULL, 0);

    SetTexture(L"D:/test.png");

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

    deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    deviceContext->Draw(6, 0);

    swapChain->swapChain->Present(1, 0);

}
