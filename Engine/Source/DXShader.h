
#pragma once

#include "Shader.h"
#include "dx.h"

class DXShader : public Shader
{
public:
    DXShader(std::string source, Type type);

    virtual void Compile() override;

    ComPtr<ID3DBlob> blob;
};
