
#pragma once

#include <vulkaninc.h>
#include "../Impl.h"
#include "../Texture.h"

class VulkanRenderer;

template <>
class Impl<Texture, RendererType::Vulkan>
{
public:
    Impl(VulkanRenderer* renderer, Texture* resource);

    void initImage(VulkanRenderer* renderer, Texture* texture);
    void initSampler(VulkanRenderer* renderer);

    VkImage image;
    VkSampler sampler;
};
