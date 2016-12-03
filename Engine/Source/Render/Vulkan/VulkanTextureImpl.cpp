
#include "VulkanTextureImpl.h"
#include <Images.h>
#include <VulkanRenderer.h>

Impl<Texture, RendererType::Vulkan>::Impl(VulkanRenderer* renderer, Texture* texture)
{
    auto sourceImage = Images::loadPng(texture->filePath);

    auto& device = renderer->getDevice();

    VkImageCreateInfo imageInfo = {};
    imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    imageInfo.imageType = VK_IMAGE_TYPE_2D;
    imageInfo.format = VK_FORMAT_R8G8B8A8_UNORM;
    imageInfo.extent = {(uint32_t)sourceImage->width, (uint32_t)sourceImage->height, 1};
    imageInfo.mipLevels = 1;
    imageInfo.arrayLayers = 1;
    imageInfo.samples = VK_SAMPLE_COUNT_1_BIT;
    imageInfo.tiling = VK_IMAGE_TILING_LINEAR;
    imageInfo.usage = VK_IMAGE_USAGE_SAMPLED_BIT;
    imageInfo.initialLayout = VK_IMAGE_LAYOUT_PREINITIALIZED;

    auto err = vkCreateImage(device, &imageInfo, nullptr, &image);
    assert(!err);

    VkMemoryRequirements memoryRequirements = {};
    vkGetImageMemoryRequirements(device, this->image, &memoryRequirements);

    VkMemoryAllocateInfo allocateInfo = {};
    allocateInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocateInfo.allocationSize = memoryRequirements.size;
    auto flags = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;
    allocateInfo.memoryTypeIndex = renderer->getMemoryTypeIndex(memoryRequirements, flags);

    VkDeviceMemory imageMemory;
    err = vkAllocateMemory(device, &allocateInfo, nullptr, &imageMemory);
    assert(!err);

    err = vkBindImageMemory(device, image, imageMemory, 0);
    assert(!err);

    //set_image_layout(info, mappableImage, VK_IMAGE_ASPECT_COLOR_BIT, VK_IMAGE_LAYOUT_PREINITIALIZED, VK_IMAGE_LAYOUT_GENERAL);

    VkImageSubresource imageSubResource = {};
    imageSubResource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    imageSubResource.mipLevel = 0;
    imageSubResource.arrayLayer = 0;
    VkSubresourceLayout subLayout;
    vkGetImageSubresourceLayout(device, image, &imageSubResource, &subLayout);

    auto size = sourceImage->getSize();
    void* data;
    err = vkMapMemory(device, imageMemory, 0, size, 0, &data);
    assert(!err);

    memcpy(data, sourceImage->data, size);
    vkUnmapMemory(device, imageMemory);

    delete sourceImage;
}
