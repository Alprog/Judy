
#pragma once

#include "../Impl.h"

class ConstantBuffer;
class GLRenderer;

template <>
class Impl<ConstantBuffer, RendererType::GL>
{
public:
    Impl(GLRenderer* renderer, ConstantBuffer* constantBuffer);
};
