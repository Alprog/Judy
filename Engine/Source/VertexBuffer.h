
#pragma once

#include "d3d12.h"
#include "wrl.h"
#include "Renderer.h"

using namespace Microsoft::WRL;

class VertexBuffer
{
public:
    VertexBuffer(Renderer* renderer);

    ComPtr<ID3D12Resource> vertexBuffer;
    ComPtr<ID3D12Resource> indexBuffer;

    D3D12_VERTEX_BUFFER_VIEW vertexBufferView;
    D3D12_INDEX_BUFFER_VIEW indexBufferView;
};
