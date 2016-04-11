
#pragma once

#include "dx.h"

class Shader;
class DXRenderer;

class DXPipelineState
{
public:
    DXPipelineState(Shader* vertexShader, Shader* pixelShader, DXRenderer* renderer);

    ComPtr<ID3D12PipelineState> pipelineState;
    ComPtr<ID3D12RootSignature> rootSignature;
};
