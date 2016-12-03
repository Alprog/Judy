
#pragma once

#include <vulkaninc.h>
#include "../Impl.h"
#include "../IndexBuffer.h"

class VulkanRenderer;

template <>
class Impl<IndexBuffer, RendererType::Vulkan>
{
public:
    Impl(VulkanRenderer* renderer, IndexBuffer* resource);

    VkBuffer buffer;
};
