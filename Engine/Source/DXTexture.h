
#pragma once

#include "dx.h"
#include <vector>

class DXRenderer;
class Image;

class DXTexture
{
public:
    DXTexture(DXRenderer* renderer, Image* image);

protected:
    std::vector<UINT8> GenerateChessboard();

public:
    ComPtr<ID3D12Resource> texture;
};
