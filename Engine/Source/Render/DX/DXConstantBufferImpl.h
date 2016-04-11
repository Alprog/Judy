
#pragma once

#include "../Impl.h"

class ConstantBuffer;
class DXRenderer;

template <>
class Impl<ConstantBuffer, RendererType::DX>
{
public:
    Impl(DXRenderer* renderer, ConstantBuffer* constantBuffer);
};
