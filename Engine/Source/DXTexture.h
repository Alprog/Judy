
#pragma once

#include "dx.h"
#include <vector>

class Renderer;

class DXTexture
{
public:
    DXTexture(Renderer* renderer);

protected:
    std::vector<UINT8> GenerateChessboard();

public:
    ComPtr<ID3D12Resource> texture;
};
