
#pragma once

#include "Shader.h"

#include <d3d12.h>
#include <wrl.h>

using namespace Microsoft::WRL;

class DXShader : public Shader
{
public:
    virtual void Compile() override;

    ComPtr<ID3DBlob> blob;
};
