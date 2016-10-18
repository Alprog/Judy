
#pragma once

#include "dx.h"

#include "DXDescriptorHandle.h"

class DXDescriptorHeap
{
public:
    DXDescriptorHeap(ID3D12Device* device, UINT maxCount);

    ID3D12DescriptorHeap* get() { return heap.Get(); }
    DXDescriptorHandle getNextHandle();

    inline CD3DX12_CPU_DESCRIPTOR_HANDLE getCpuHandle(int index)
    {
        return {cpuHandle, index * handleIncrementSize};
    }

    inline CD3DX12_GPU_DESCRIPTOR_HANDLE getGpuHandle(int index)
    {
        return {gpuHandle, index * handleIncrementSize};
    }

private:
    ComPtr<ID3D12DescriptorHeap> heap;

    CD3DX12_CPU_DESCRIPTOR_HANDLE cpuHandle;
    CD3DX12_GPU_DESCRIPTOR_HANDLE gpuHandle;
    int handleIncrementSize;

    int descriptorCount;
    int maxCount;
};
