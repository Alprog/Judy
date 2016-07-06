
#pragma once

#include "../Shader.h"
#include "dx.h"
#include "../Impl.h"
#include "../Shader.h"

class DXRenderer;

template <>
class Impl<Shader, RendererType::DX>
{
public:
    Impl(DXRenderer* renderer, Shader* shader);
    ComPtr<ID3DBlob> blob;
};
