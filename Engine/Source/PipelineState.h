
#pragma once

#include "dx.h"

class DXShader;
class DXRenderer;

class DXPipelineState
{
public:
    DXPipelineState(DXShader* vertexShader, DXShader* pixelShader, DXRenderer* renderer);

    ComPtr<ID3D12PipelineState> pipelineState;
    ComPtr<ID3D12RootSignature> rootSignature;
};
