
#pragma once

#include "dx.h"
#include "d3dx12.h"

#include "DXDescriptorHandle.h"

class DXDescriptorHeap
{
public:
    DXDescriptorHeap(ID3D12Device* device, UINT maxCount);

    DXDescriptorHandle GetNextHandle();

    inline CD3DX12_CPU_DESCRIPTOR_HANDLE GetCpuHandle(int index)
    {
        return {cpuHandle, index * handleIncrementSize};
    }

    inline CD3DX12_GPU_DESCRIPTOR_HANDLE GetGpuHandle(int index)
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
