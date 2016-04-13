
#include "DXIndexBufferImpl.h"
#include "DXRenderer.h"
#include "d3dx12.h"
#include "../IndexBuffer.h"

Impl<IndexBuffer, RendererType::DX>::Impl(DXRenderer* renderer, IndexBuffer* ib)
{
    auto device = renderer->GetDevice();

    unsigned int indices[] = {
        0, 1, 2, 0, 2, 3,
        4, 5, 6, 4, 6, 7,
        8, 9, 10, 8, 10, 11,
        12, 13, 14, 12, 14, 15,
        16, 17, 18, 16, 18, 19,
        20, 21, 22, 20, 22, 23
     };
    const UINT indexBufferSize = sizeof(indices);

    auto result = device->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD), D3D12_HEAP_FLAG_NONE,
            &CD3DX12_RESOURCE_DESC::Buffer(indexBufferSize), D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&indexBuffer));
    if (FAILED(result)) throw;

    UINT8* data;
    CD3DX12_RANGE readRange(0, 0);

    result = indexBuffer->Map(0, &readRange, reinterpret_cast<void**>(&data));
    if (FAILED(result)) throw;
    memcpy(data, indices, sizeof(indices));
    indexBuffer->Unmap(0, nullptr);

    indexBufferView.BufferLocation = indexBuffer->GetGPUVirtualAddress();
    indexBufferView.Format = DXGI_FORMAT::DXGI_FORMAT_R32_UINT;
    indexBufferView.SizeInBytes = indexBufferSize;
}
