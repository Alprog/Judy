
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
    void initImageView(VulkanRenderer* renderer);
    void initSampler(VulkanRenderer* renderer);
    void initDescriptorSet(VulkanRenderer* renderer);

    VkImage image;
    VkImageView imageView;
    VkSampler sampler;
    VkDescriptorSet descriptorSet;
};
