
#pragma once

#include "../Impl.h"
#include "dx.h"
#include "Matrix.h"
#include "DXDescriptorHandle.h"
#include "../ConstantBuffer.h"

class DXRenderer;

template <>
class Impl<ConstantBuffer, RendererType::DX>
{
public:
    Impl(DXRenderer* renderer, ConstantBuffer* resource);
    void update();

    ComPtr<ID3D12Resource> constantBuffer;
    DXDescriptorHandle descriptorHandle;

    ConstantBuffer* resource;
    int version;
    UINT8* gpuDataBegin;
};
