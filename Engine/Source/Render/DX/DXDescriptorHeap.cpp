
#include "DXDescriptorHeap.h"

DXDescriptorHeap::DXDescriptorHeap(ID3D12Device* device, UINT maxCount)
{
    D3D12_DESCRIPTOR_HEAP_DESC desc;
    desc.NumDescriptors = maxCount;
    desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
    desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;

    this->descriptorCount = 0;
    this->maxCount = maxCount;

    auto result = device->CreateDescriptorHeap(&desc, IID_PPV_ARGS(&heap));
    if (FAILED(result)) throw;

    cpuHandle = heap->GetCPUDescriptorHandleForHeapStart();
    gpuHandle = heap->GetGPUDescriptorHandleForHeapStart();

    handleIncrementSize = device->GetDescriptorHandleIncrementSize(desc.Type);
}

DXDescriptorHandle DXDescriptorHeap::GetNextHandle()
{
    return DXDescriptorHandle(this, descriptorCount);
    descriptorCount++;
}
