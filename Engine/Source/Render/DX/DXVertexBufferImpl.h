
#pragma once

#include "dx.h"
#include "../Impl.h"
#include "../VertexBuffer.h"

class DXRenderer;

template <>
class Impl<VertexBuffer, RendererType::DX>
{
public:
    Impl(DXRenderer* renderer, VertexBuffer* vertexBuffer);

    ComPtr<ID3D12Resource> vertexBuffer;
    D3D12_VERTEX_BUFFER_VIEW vertexBufferView;
};
