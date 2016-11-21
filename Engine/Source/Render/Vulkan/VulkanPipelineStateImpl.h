
#pragma once

#include <Impl.h>
#include <PipelineState.h>

class VulkanRenderer;

template <>
class Impl<PipelineState, RendererType::Vulkan>
{
public:
    Impl(VulkanRenderer* renderer, PipelineState* pipelineState);
};
