
#include "VulkanShaderImpl.h"
#include <ShaderBunch.h>
#include <VulkanRenderer.h>
#include <cassert>

Impl<Shader, RendererType::Vulkan>::Impl(VulkanRenderer* renderer, Shader* resource)
{
    bool isVertex = resource->type == ShaderType::Vertex;

    auto blobType = isVertex ? ShaderBunch::BlobType::SpirvVertex : ShaderBunch::BlobType::SpirvPixel;
    auto blob = resource->bunch->getSource(blobType);

    VkShaderModuleCreateInfo moduleInfo = {};
    moduleInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    moduleInfo.pNext = nullptr;
    moduleInfo.codeSize = blob.size();
    moduleInfo.pCode = (const uint32_t*)blob.data();
    moduleInfo.flags = 0;

    auto err = vkCreateShaderModule(renderer->getDevice(), &moduleInfo, nullptr, &shaderModule);
    assert(!err);

    shaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    shaderStageInfo.pNext = nullptr;
    shaderStageInfo.flags = 0;
    shaderStageInfo.stage = isVertex ? VK_SHADER_STAGE_VERTEX_BIT : VK_SHADER_STAGE_FRAGMENT_BIT;
    shaderStageInfo.module = shaderModule;
    shaderStageInfo.pName = resource->entryPoint.c_str();
    shaderStageInfo.pSpecializationInfo = nullptr;
}
