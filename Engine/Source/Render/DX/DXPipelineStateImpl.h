
#pragma once

#include "dx.h"
#include <Impl.h>
#include <PipelineState.h>

class DXRenderer;

template <>
class Impl<PipelineState, RendererType::DX>
{
public:
    Impl(DXRenderer* renderer, PipelineState* pipelineState);

    ComPtr<ID3D12PipelineState> pipelineState;
    ComPtr<ID3D12RootSignature> rootSignature;
};
