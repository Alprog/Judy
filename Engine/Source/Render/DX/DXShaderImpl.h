
#pragma once

#include "../Shader.h"
#include "dx.h"
#include "../Impl.h"

class DXRenderer;
class Shader;

template <>
class Impl<Shader, RendererType::DX>
{
public:
    Impl(DXRenderer* renderer, Shader* shader);
    ComPtr<ID3DBlob> blob;
};
