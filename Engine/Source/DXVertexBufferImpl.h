
#pragma once

#include "dx.h"

class DXRenderer;
class VertexBuffer;

class DXVertexBufferImpl
{
public:
    DXVertexBufferImpl(DXRenderer* renderer, VertexBuffer* vertexBuffer);

    ComPtr<ID3D12Resource> vertexBuffer;
    ComPtr<ID3D12Resource> indexBuffer;

    D3D12_VERTEX_BUFFER_VIEW vertexBufferView;
    D3D12_INDEX_BUFFER_VIEW indexBufferView;
};
