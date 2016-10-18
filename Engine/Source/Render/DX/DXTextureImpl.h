
#pragma once

#include "dx.h"
#include <vector>
#include "../Impl.h"

#include "DXDescriptorHandle.h"
#include "../Texture.h"

class DXRenderer;

template <>
class Impl<Texture, RendererType::DX>
{
public:
    Impl(DXRenderer* renderer, Texture* resource);

protected:
    std::vector<UINT8> generateChessboard();

public:
    ComPtr<ID3D12Resource> texture;
    DXDescriptorHandle descriptorHandle;
};
