
#pragma once

#include "../Impl.h"
#include "dx.h"
#include "Matrix.h"
#include "DXDescriptorHandle.h"

class ConstantBuffer;
class DXRenderer;

template <>
class Impl<ConstantBuffer, RendererType::DX>
{
public:
    Impl(DXRenderer* renderer, ConstantBuffer* constantBuffer);

    void Update();

    ComPtr<ID3D12Resource> constantBuffer;

    struct
    {
        Matrix MVP;
    }
    data;

    UINT8* gpuDataBegin;

    DXDescriptorHandle descriptorHandle;
};
