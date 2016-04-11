
#include "DXVertexBufferImpl.h"

#include "d3dx12.h"
#include "Vector3.h"
#include "Vector4.h"
#include "DXRenderer.h"
#include "DirectXMath.h"

struct VertexA
{
    Vector3 position;
    Vector4 color;
    Vector2 texcoord;
};

Impl<VertexBuffer, RendererType::DX>::Impl(DXRenderer* renderer, VertexBuffer* vb)
{
    auto device = renderer->GetDevice();

    VertexA triangleVertices[] =
    {
        { { 0.0f, 0.5f * 1, 0.0f }, { 1.0f, 0.0f, 0.0f, 1.0f }, { 0.5f, 0.0f } },
        { { 0.25f, -0.25f * 1, 0.0f }, { 0.0f, 1.0f, 0.0f, 1.0f }, { 1.0f, 1.0f } },
        { { -0.25f, -0.25f * 1, 0.0f }, { 0.0f, 0.0f, 1.0f, 1.0f }, { 0.0f, 1.0f } }
    };

    const UINT vertexBufferSize = sizeof(triangleVertices);


    auto result = device->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD), D3D12_HEAP_FLAG_NONE,
        &CD3DX12_RESOURCE_DESC::Buffer(vertexBufferSize), D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&vertexBuffer));

    if (FAILED(result)) throw;

    UINT8* data;
    CD3DX12_RANGE readRange(0, 0);

    result = vertexBuffer->Map(0, &readRange, reinterpret_cast<void**>(&data));
    if (FAILED(result)) throw;
    memcpy(data, triangleVertices, sizeof(triangleVertices));
    vertexBuffer->Unmap(0, nullptr);

    vertexBufferView.BufferLocation = vertexBuffer->GetGPUVirtualAddress();
    vertexBufferView.StrideInBytes = sizeof(VertexA);
    vertexBufferView.SizeInBytes = vertexBufferSize;
}

