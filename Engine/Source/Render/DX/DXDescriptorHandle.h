
#pragma once

#include "dx.h"
#include "d3dx12.h"

class DXDescriptorHeap;

struct DXDescriptorHandle
{
    DXDescriptorHandle();
    DXDescriptorHandle(DXDescriptorHeap* heap, int index);

    CD3DX12_CPU_DESCRIPTOR_HANDLE GetCPU();
    CD3DX12_GPU_DESCRIPTOR_HANDLE GetGPU();

private:
    DXDescriptorHeap* heap;
    int index;
};
