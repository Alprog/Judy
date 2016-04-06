
#pragma once

#include "dx.h"
#include <vector>

class DXRenderer;
class Texture;

class DXTexture
{
public:
    DXTexture(DXRenderer* renderer, Texture* resource);

protected:
    std::vector<UINT8> GenerateChessboard();

public:
    ComPtr<ID3D12Resource> texture;
};
