
#include "DXVertexBufferImpl.h"

#include "d3dx12.h"
#include "Vector3.h"
#include "Vector4.h"
#include "DXRenderer.h"
#include "DirectXMath.h"
#include "../VertexBuffer.h"

struct VertexA
{
    Vector3 position;
    Vector2 texcoord;
};

Impl<VertexBuffer, RendererType::DX>::Impl(DXRenderer* renderer, VertexBuffer* vb)
{
    auto device = renderer->GetDevice();

    const UINT vertexBufferSize = sizeof(VertexA) * vb->vertices.size();

    printf("SIZE: %i\n", vertexBufferSize);

    auto result = device->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD), D3D12_HEAP_FLAG_NONE,
        &CD3DX12_RESOURCE_DESC::Buffer(vertexBufferSize), D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&vertexBuffer));

    if (FAILED(result)) throw;

    UINT8* data;
    CD3DX12_RANGE readRange(0, 0);

    result = vertexBuffer->Map(0, &readRange, reinterpret_cast<void**>(&data));
    if (FAILED(result)) throw;
    memcpy(data, &vb->vertices[0], vertexBufferSize);
    vertexBuffer->Unmap(0, nullptr);

    vertexBufferView.BufferLocation = vertexBuffer->GetGPUVirtualAddress();
    vertexBufferView.StrideInBytes = sizeof(VertexA);
    vertexBufferView.SizeInBytes = vertexBufferSize;
}

