
#include "VertexBuffer.h"

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

VertexBuffer::VertexBuffer(Renderer* renderer)
{
    auto device = static_cast<DXRenderer*>(renderer)->GetDevice();

    VertexA triangleVertices[] =
    {
        { { 0.0f, 0.5f * 1, 0.0f }, { 1.0f, 0.0f, 0.0f, 1.0f }, { 0.5f, 0.0f } },
        { { 0.25f, -0.25f * 1, 0.0f }, { 0.0f, 1.0f, 0.0f, 1.0f }, { 1.0f, 1.0f } },
        { { -0.25f, -0.25f * 1, 0.0f }, { 0.0f, 0.0f, 1.0f, 1.0f }, { 0.0f, 1.0f } }
    };

    unsigned int indices[] = { 0, 1, 2 };

    const UINT vertexBufferSize = sizeof(triangleVertices);
    const UINT indexBufferSize = sizeof(indices);

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

    result = device->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD), D3D12_HEAP_FLAG_NONE,
            &CD3DX12_RESOURCE_DESC::Buffer(indexBufferSize), D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&indexBuffer));
    if (FAILED(result)) throw;

    result = indexBuffer->Map(0, &readRange, reinterpret_cast<void**>(&data));
    if (FAILED(result)) throw;
    memcpy(data, indices, sizeof(indices));
    indexBuffer->Unmap(0, nullptr);


    indexBufferView.BufferLocation = indexBuffer->GetGPUVirtualAddress();
    indexBufferView.Format = DXGI_FORMAT::DXGI_FORMAT_R32_UINT;
    indexBufferView.SizeInBytes = indexBufferSize;
}

