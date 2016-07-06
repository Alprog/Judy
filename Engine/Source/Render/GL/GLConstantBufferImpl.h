
#pragma once

#include "../Impl.h"
#include "../ConstantBuffer.h"

class GLRenderer;

template <>
class Impl<ConstantBuffer, RendererType::GL>
{
public:
    Impl(GLRenderer* renderer, ConstantBuffer* constantBuffer);
};
