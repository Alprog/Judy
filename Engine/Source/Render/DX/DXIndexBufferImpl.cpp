
#include "DXIndexBufferImpl.h"
#include "DXRenderer.h"

Impl<IndexBuffer, RendererType::DX>::Impl(DXRenderer* renderer, IndexBuffer* ib)
{
    auto device = renderer->getDevice();

    const UINT indexBufferSize = ib->indices.size() * sizeof(uint32_t);

    auto result = device->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD), D3D12_HEAP_FLAG_NONE,
            &CD3DX12_RESOURCE_DESC::Buffer(indexBufferSize), D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&indexBuffer));
    if (FAILED(result)) throw;

    UINT8* data;
    CD3DX12_RANGE readRange(0, 0);

    result = indexBuffer->Map(0, &readRange, reinterpret_cast<void**>(&data));
    if (FAILED(result)) throw;
    memcpy(data, &ib->indices[0], indexBufferSize);
    indexBuffer->Unmap(0, nullptr);

    indexBufferView.BufferLocation = indexBuffer->GetGPUVirtualAddress();
    indexBufferView.Format = DXGI_FORMAT::DXGI_FORMAT_R32_UINT;
    indexBufferView.SizeInBytes = indexBufferSize;
}
