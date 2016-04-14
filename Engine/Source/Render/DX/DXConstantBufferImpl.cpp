
#include "DXConstantBufferImpl.h"
#include "DXRenderer.h"
#include "d3dx12.h"

#include "DXDescriptorHeap.h"

Impl<ConstantBuffer, RendererType::DX>::Impl(DXRenderer* renderer, ConstantBuffer* cb)
{
    auto device = renderer->GetDevice();

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
    cbvDesc.SizeInBytes = (sizeof(data) + 255) & ~255;

    auto heap = renderer->GetSrvCbvHeap();

    device->CreateConstantBufferView(&cbvDesc, heap->GetCpuHandle(1));

    ZeroMemory(&data, sizeof(data));

    data.MVP = Matrix::Identity;

    CD3DX12_RANGE readRange(0, 0);
    result = constantBuffer->Map(0, &readRange, reinterpret_cast<void**>(&gpuDataBegin));
    if (FAILED(result)) throw;

    Update();
}

void Impl<ConstantBuffer, RendererType::DX>::Update()
{
    memcpy(gpuDataBegin, &data, sizeof(data));
}

