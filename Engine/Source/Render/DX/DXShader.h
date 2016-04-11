
#pragma once

#include "../Shader.h"
#include "dx.h"

class DXShader
{
public:
    DXShader(std::string source, Shader::Type type);
    ComPtr<ID3DBlob> blob;
};
