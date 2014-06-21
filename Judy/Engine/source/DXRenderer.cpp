
#include "DXRenderer.h"

#include <d3d11.h>
#include <DXGI.h>
#include <d3dcompiler.h>

#include <stdio.h>
#include <iostream>

ID3D11Device* device = nullptr;
ID3D11DeviceContext* deviceContext = nullptr;
IDXGISwapChain* swapChain = nullptr;
ID3D11RenderTargetView* view = nullptr;

ID3D11VertexShader* vs;
ID3D11PixelShader* ps;
ID3D11InputLayout* layout;

ID3D11Buffer* vertexBuffer;
ID3D11Buffer* constantBuffer;

struct D3DXVECTOR3 {
  FLOAT x;
  FLOAT y;
  FLOAT z;
};

struct D3DXVECTOR4 {
  FLOAT x;
  FLOAT y;
  FLOAT z;
  FLOAT w;
};

struct D3DMATRIX {
    union {
        struct {
            float        _11, _12, _13, _14;
            float        _21, _22, _23, _24;
            float        _31, _32, _33, _34;
            float        _41, _42, _43, _44;

        };
        float m[4][4];
    };
};

struct ConstantBufferType
{
    D3DMATRIX world;
    D3DMATRIX view;
    D3DMATRIX projection;
};


struct VertexType
{
    D3DXVECTOR3 position;
    D3DXVECTOR4 color;
};


DXRenderer::DXRenderer()
{
    auto type = D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_HARDWARE;

    auto featureLevels = D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_11_0;
    D3D_FEATURE_LEVEL featureLevel;

    HRESULT a = D3D11CreateDevice(NULL, type, NULL, 0, &featureLevels, 1, D3D11_SDK_VERSION, &device, &featureLevel, &deviceContext);


}

void DXRenderer::Render(Scene* scene, HWND hWnd)
{
    if (!swapChain)
    {
        DXGI_SWAP_CHAIN_DESC desc;
        ZeroMemory(&desc, sizeof(desc));
        desc.BufferCount = 1;
        desc.BufferDesc.Width = 640;
        desc.BufferDesc.Height = 480;
        desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        desc.BufferDesc.RefreshRate.Numerator = 60;
        desc.BufferDesc.RefreshRate.Denominator = 1;
        desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        desc.OutputWindow = hWnd;
        desc.SampleDesc.Count = 1;
        desc.SampleDesc.Quality = 0;
        desc.Windowed = TRUE;

        IDXGIFactory* factory;
        CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory);
        factory->CreateSwapChain(device, &desc, &swapChain);

        ID3D11Texture2D* backBuffer;
        swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBuffer);
        device->CreateRenderTargetView(backBuffer, NULL, &view);


        auto vsfile = L"D:\\Metroidvania\\Judy\\Engine\\source\\color.vs";
        auto psfile = L"D:\\Metroidvania\\Judy\\Engine\\source\\color.ps";

        ID3DBlob* vscode;
        ID3DBlob* pscode;
        ID3DBlob* message;

        HRESULT a;

        a = D3DCompileFromFile(vsfile, NULL, NULL, "ColorVertexShader", "vs_5_0", 0, 0, &vscode, &message);
        printf("%i", a); fflush(stdout);
        a = D3DCompileFromFile(psfile, NULL, NULL, "ColorPixelShader", "ps_5_0", 0, 0, &pscode, &message);
        printf("%i", a); fflush(stdout);
        a = device->CreateVertexShader(vscode->GetBufferPointer(), vscode->GetBufferSize(), NULL, &vs);
        printf("%i", a); fflush(stdout);
        a = device->CreatePixelShader(pscode->GetBufferPointer(), pscode->GetBufferSize(), NULL, &ps);
        printf("%i", a); fflush(stdout);

        D3D11_INPUT_ELEMENT_DESC element_desc[2];
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

        a = device->CreateInputLayout(element_desc, 2, vscode->GetBufferPointer(), vscode->GetBufferSize(), &layout);
        printf("%i", a); fflush(stdout);

        VertexType vertices[3];
        vertices[0].position = {-1.0f, -1.0f, 0.0f};
        vertices[1].position = {0.0f, 1.0f, 0.0f};
        vertices[2].position = {1.0f, -1.0f, 0.0f};
        vertices[0].color = {0.0f, 1.0f, 0.0f, 1.0f};
        vertices[1].color = {0.0f, 1.0f, 0.0f, 1.0f};
        vertices[2].color = {0.0f, 1.0f, 0.0f, 1.0f};

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
        printf("%i", a); fflush(stdout);

        D3D11_BUFFER_DESC constantBufferDesc;
        constantBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
        constantBufferDesc.ByteWidth = sizeof(ConstantBufferType);
        constantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
        constantBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
        constantBufferDesc.MiscFlags = 0;
        constantBufferDesc.StructureByteStride = 0;

        a = device->CreateBuffer(&constantBufferDesc, NULL, &constantBuffer);
        printf("%i", a); fflush(stdout);

        D3D11_VIEWPORT viewport;
        viewport.TopLeftX = 0;
        viewport.TopLeftY = 0;
        viewport.Width = 800;
        viewport.Height = 800;
        viewport.MinDepth = 0.0f;
        viewport.MaxDepth = 1.0f;
        deviceContext->RSSetViewports(1, &viewport);

        /*D3D11_RECT rect;
        rect.bottom = 0;
        rect.top = 0;
        rect.right = 400;
        rect.bottom = 800;
        deviceContext->RSSetScissorRects(1, &rect);*/


        D3D11_RASTERIZER_DESC rsdesc;
        rsdesc.FillMode = D3D11_FILL_SOLID;
        rsdesc.CullMode = D3D11_CULL_NONE;
        rsdesc.FrontCounterClockwise = true;
        rsdesc.DepthBias = false;
        rsdesc.DepthBiasClamp = 0;
        rsdesc.SlopeScaledDepthBias = 0;
        rsdesc.DepthClipEnable = false;
        rsdesc.ScissorEnable = false;
        rsdesc.MultisampleEnable = false;
        rsdesc.AntialiasedLineEnable = false;

        ID3D11RasterizerState* rsstate;
        a = device->CreateRasterizerState(&rsdesc, &rsstate);
        printf("%i", a); fflush(stdout);

        deviceContext->RSSetState(rsstate);
    }

    deviceContext->OMSetRenderTargets(1, &view, NULL);


    float color[4];
    color[0] = 0;
    color[1] = 0;
    color[2] = 1;
    color[3] = 0;

    deviceContext->ClearRenderTargetView(view, color);

    unsigned int stride = sizeof(VertexType);
    unsigned int offset = 0;

    deviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
    //deviceContext->VSSetConstantBuffers(0, 1, &constantBuffer);
    //deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

    deviceContext->IASetInputLayout(layout);
    deviceContext->VSSetShader(vs, NULL, 0);
    deviceContext->PSSetShader(ps, NULL, 0);
    //deviceContext->DrawIndexed(indexCount, 0, 0);

    deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    deviceContext->Draw(3, 0);

    swapChain->Present(0, 0);
}

void DXRenderer::Render(Scene *scene, Context *context)
{

}
