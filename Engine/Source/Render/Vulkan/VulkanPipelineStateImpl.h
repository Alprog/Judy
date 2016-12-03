
#pragma once

#include <Impl.h>
#include <PipelineState.h>
#include <vulkaninc.h>

class VulkanRenderer;

template <>
class Impl<PipelineState, RendererType::Vulkan>
{
public:
    Impl(VulkanRenderer* renderer, PipelineState* pipelineState);

    VkPipeline pipeline;
    VkPipelineLayout pipelineLayout;

    VkRenderPass renderPass;

private:
    void initRenderPass(VulkanRenderer* renderer, VkFormat colorFormat, VkFormat depthFormat);
};
