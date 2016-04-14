
#include "DXDescriptorHandle.h"
#include "DXDescriptorHeap.h"

DXDescriptorHandle::DXDescriptorHandle()
    : heap {nullptr}
    , index {0}
{
}

DXDescriptorHandle::DXDescriptorHandle(DXDescriptorHeap* heap, int index)
    : heap {heap}
    , index {index}
{
}

CD3DX12_CPU_DESCRIPTOR_HANDLE DXDescriptorHandle::GetCPU()
{
    return heap->GetCpuHandle(index);
}

CD3DX12_GPU_DESCRIPTOR_HANDLE DXDescriptorHandle::GetGPU()
{
    return heap->GetGpuHandle(index);
}
