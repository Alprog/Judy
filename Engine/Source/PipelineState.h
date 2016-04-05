
#pragma once

#include <d3d12.h>
#include <wrl.h>

using namespace Microsoft::WRL;

class Shader;
class DXRenderer;

class PipelineState
{
public:
    PipelineState(Shader* vertexShader, Shader* pixelShader, DXRenderer* renderer);

    ComPtr<ID3D12PipelineState> pipelineState;
    ComPtr<ID3D12RootSignature> rootSignature;
};
