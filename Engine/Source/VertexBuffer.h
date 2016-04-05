
#pragma once

#include "Renderer.h"
#include "dx.h"

class VertexBuffer
{
public:
    VertexBuffer(Renderer* renderer);

    ComPtr<ID3D12Resource> vertexBuffer;
    ComPtr<ID3D12Resource> indexBuffer;

    D3D12_VERTEX_BUFFER_VIEW vertexBufferView;
    D3D12_INDEX_BUFFER_VIEW indexBufferView;
};
