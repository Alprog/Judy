
#include "DXConstantBufferImpl.h"
#include "DXRenderer.h"
#include "DXDescriptorHeap.h"

Impl<ConstantBuffer, RendererType::DX>::Impl(DXRenderer* renderer, ConstantBuffer* cb)
    : resource{cb}
    , version{0}
{
    auto device = renderer->getDevice();

    auto result = device->CreateCommittedResource(
        &CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
        D3D12_HEAP_FLAG_NONE,
        &CD3DX12_RESOURCE_DESC::Buffer(1024 * 64),
        D3D12_RESOURCE_STATE_GENERIC_READ,
        nullptr,
        IID_PPV_ARGS(&constantBuffer));

    if (FAILED(result)) throw;

    D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc = {};
    cbvDesc.BufferLocation = constantBuffer->GetGPUVirtualAddress();
    cbvDesc.SizeInBytes = (sizeof(resource->data) + 255) & ~255;

    descriptorHandle = renderer->getSrvCbvHeap()->getNextHandle();
    device->CreateConstantBufferView(&cbvDesc, descriptorHandle.getCPU());

    CD3DX12_RANGE readRange(0, 0);
    result = constantBuffer->Map(0, &readRange, reinterpret_cast<void**>(&gpuDataBegin));
    if (FAILED(result)) throw;

    update();
}

void Impl<ConstantBuffer, RendererType::DX>::update()
{
    if (version != resource->version)
    {
        memcpy(gpuDataBegin, &resource->data, sizeof(resource->data));
        version = resource->version;
    }
}

