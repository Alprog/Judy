
#pragma once

#include "dx.h"
#include <vector>
#include "../Impl.h"

class DXRenderer;
class Texture;

template <>
class Impl<Texture, RendererType::DX>
{
public:
    Impl(DXRenderer* renderer, Texture* resource);

protected:
    std::vector<UINT8> GenerateChessboard();

public:
    ComPtr<ID3D12Resource> texture;
};
