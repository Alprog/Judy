
#pragma once

#include "Shader.h"

#include <d3d12.h>
#include <wrl.h>

using namespace Microsoft::WRL;

class DXShader : public Shader
{
public:
    DXShader(std::string source, Type type);

    virtual void Compile() override;

    ComPtr<ID3DBlob> blob;
};
