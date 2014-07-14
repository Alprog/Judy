
#include "DXRenderer.h"

#include "Vector.h"
#include "Matrix.h"

#include <DXGI1_2.h>
#include <d3dcompiler.h>

#include <stdio.h>
#include <iostream>

#include <d3dx11.h>

#include "DXSwapChain.h"

ID3D11VertexShader* vs;
ID3D11PixelShader* ps;
ID3D11InputLayout* layout;
ID3D11Buffer* vertexBuffer;
ID3D11Buffer* constantBuffer;

DXSwapChain* swapChain = nullptr;

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
    deviceContext->ClearRenderTargetView(swapChain->view, color.data);
}

void DXRenderer::SetTexture(std::wstring name)
{
    auto texture = (ID3D11ShaderResourceView*)textures[name];
    if (texture == nullptr)
    {
        D3DX11CreateShaderResourceViewFromFile(device, name.c_str(), NULL, NULL, &texture, NULL);
        textures[name] = texture;
    }
    deviceContext->PSSetShaderResources(0, 1, &texture);
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

void DXRenderer::SetRenderTarget(DXSwapChain* swapChain)
{
    deviceContext->OMSetRenderTargets(1, &swapChain->view, NULL);
}

void DXRenderer::Render(Scene* scene, HWND hWnd)
{
    if (swapChain == nullptr)
    {
        swapChain = new DXSwapChain(this, hWnd);

        auto vsfile = L"D:\\Metroidvania\\Judy\\Engine\\source\\color.vs";
        auto psfile = L"D:\\Metroidvania\\Judy\\Engine\\source\\color.ps";

        ID3DBlob* vscode;
        ID3DBlob* pscode;
        ID3DBlob* message;

        HRESULT a;

        a = D3DCompileFromFile(vsfile, NULL, NULL, "ColorVertexShader", "vs_5_0", 0, 0, &vscode, &message);
        printf("VS:%X;", a); fflush(stdout);
        a = D3DCompileFromFile(psfile, NULL, NULL, "ColorPixelShader", "ps_5_0", 0, 0, &pscode, &message);
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

        VertexType vertices[3];
        vertices[0].position = {-0.8f, -0.8f, 0.0f};
        vertices[1].position = {0.0f, 0.8f, 0.0f};
        vertices[2].position = {0.8f, -0.8f, 0.0f};

        vertices[0].uv = {0.0f, 0.0f};
        vertices[1].uv = {0.4f, 0.8f};
        vertices[2].uv = {0.8f, 0.0f};

        vertices[0].color = {1.0f, 0.0f, 0.0f, 1.0f};
        vertices[1].color = {0.0f, 1.0f, 0.0f, 1.0f};
        vertices[2].color = {0.0f, 0.0f, 1.0f, 1.0f};

        D3D11_SUBRESOURCE_DATA vertexData;
        vertexData.pSysMem = vertices;
        vertexData.SysMemPitch = 0;
        vertexData.SysMemSlicePitch = 0;

        D3D11_BUFFER_DESC vertexBufferDesc;
        vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
        vertexBufferDesc.ByteWidth = sizeof(VertexType) * 3;
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

        SetFocus(hWnd);
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

    SetRenderTarget(swapChain);

    Color color { 0.0f, 0.0f, 1.0f, 1.0f };
    Clear(color);

    unsigned int stride = sizeof(VertexType);
    unsigned int offset = 0;

    deviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
    //deviceContext->VSSetConstantBuffers(0, 1, &constantBuffer);
    //deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

    deviceContext->IASetInputLayout(layout);
    deviceContext->VSSetShader(vs, NULL, 0);
    deviceContext->PSSetShader(ps, NULL, 0);

    SetTexture(L"D:/test.png");

    ID3D11SamplerState* state = NULL;
    deviceContext->PSSetSamplers(0, 1, &state);

    deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    deviceContext->Draw(3, 0);

    swapChain->Swap();

}

void DXRenderer::Render(Scene *scene, SwapChain *context)
{

}
