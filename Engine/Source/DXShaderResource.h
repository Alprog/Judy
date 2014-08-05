
#pragma once

#include <d3d11.h>
#include <string>

class DXShaderResource
{
public:
    DXShaderResource(ID3D11Device* device, std::wstring name);

    ID3D11VertexShader* vertexShader;
    ID3D11PixelShader* pixelShader;
    ID3D11InputLayout* inputLayout;
};

