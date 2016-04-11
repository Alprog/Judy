
#pragma once

#include "dx.h"
#include "../Impl.h"

class DXRenderer;
class VertexBuffer;

template <>
class Impl<VertexBuffer, RendererType::DX>
{
public:
    Impl(DXRenderer* renderer, VertexBuffer* vertexBuffer);

    ComPtr<ID3D12Resource> vertexBuffer;
    D3D12_VERTEX_BUFFER_VIEW vertexBufferView;
};
