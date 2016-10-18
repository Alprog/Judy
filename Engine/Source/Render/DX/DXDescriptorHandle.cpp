
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

CD3DX12_CPU_DESCRIPTOR_HANDLE DXDescriptorHandle::getCPU()
{
    return heap->getCpuHandle(index);
}

CD3DX12_GPU_DESCRIPTOR_HANDLE DXDescriptorHandle::getGPU()
{
    return heap->getGpuHandle(index);
}
