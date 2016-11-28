
#pragma once

#include <vulkaninc.h>
#include "../Impl.h"
#include "../ConstantBuffer.h"

class VulkanRenderer;

template <>
class Impl<ConstantBuffer, RendererType::Vulkan>
{
public:
    Impl(VulkanRenderer* renderer, ConstantBuffer* resource);
    void update();

    VkDescriptorSet descSet;

private:
    VulkanRenderer* renderer;
    VkDeviceMemory constantBufferMemory;
    ConstantBuffer* resource;
    int version;

    VkBuffer buffer;
};
