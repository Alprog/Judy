
#include "DXShaderResource.h"

#include "d3dcompiler.h"

DXShaderResource::DXShaderResource(ID3D11Device* device, std::wstring name)
{
    ID3DBlob* vscode;
    ID3DBlob* pscode;
    ID3DBlob* message = nullptr;

    auto vsfile = name + L".vs";
    auto psfile = name + L".ps";

    auto flags = D3DCOMPILE_ENABLE_BACKWARDS_COMPATIBILITY;

    D3DCompileFromFile(vsfile.c_str(), NULL, NULL, "ColorVertexShader", "vs_5_0", flags, 0, &vscode, &message);
    device->CreateVertexShader(vscode->GetBufferPointer(), vscode->GetBufferSize(), NULL, &vertexShader);

    D3DCompileFromFile(psfile.c_str(), NULL, NULL, "ColorPixelShader", "ps_5_0", flags, 0, &pscode, &message);
    device->CreatePixelShader(pscode->GetBufferPointer(), pscode->GetBufferSize(), NULL, &pixelShader);

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

    device->CreateInputLayout(element_desc, 3, vscode->GetBufferPointer(), vscode->GetBufferSize(), &inputLayout);
}
