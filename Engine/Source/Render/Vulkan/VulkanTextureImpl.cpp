
#include "VulkanTextureImpl.h"
#include <Images.h>
#include <VulkanRenderer.h>

using VulkanTexImpl = Impl<Texture, RendererType::Vulkan>;

VulkanTexImpl::Impl(VulkanRenderer* renderer, Texture* texture)
{
    initImage(renderer, texture);
    initImageView(renderer);
    initSampler(renderer);
    initDescriptorSet(renderer);
}

void VulkanTexImpl::initImage(VulkanRenderer* renderer, Texture* texture)
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

    auto oldStage = VK_IMAGE_LAYOUT_PREINITIALIZED;
    auto newStage = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    auto srcAccess = VK_ACCESS_HOST_WRITE_BIT;
    auto dstAccess = (VkAccessFlagBits)(VK_ACCESS_SHADER_READ_BIT | VK_ACCESS_INPUT_ATTACHMENT_READ_BIT);
    renderer->resourceBarrier(image, oldStage, newStage, srcAccess, dstAccess);

    delete sourceImage;
}

void VulkanTexImpl::initImageView(VulkanRenderer* renderer)
{
    VkImageViewCreateInfo imageViewInfo = {};
    imageViewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    imageViewInfo.image = image;
    imageViewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
    imageViewInfo.format = VK_FORMAT_R8G8B8A8_UNORM;
    imageViewInfo.components = {VK_COMPONENT_SWIZZLE_R, VK_COMPONENT_SWIZZLE_G, VK_COMPONENT_SWIZZLE_B, VK_COMPONENT_SWIZZLE_A};
    imageViewInfo.subresourceRange = {VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1};

    auto err = vkCreateImageView(renderer->getDevice(), &imageViewInfo, nullptr, &imageView);
    assert(!err);
}

void VulkanTexImpl::initSampler(VulkanRenderer* renderer)
{
    VkSamplerCreateInfo samplerInfo = {};
    samplerInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
    samplerInfo.magFilter = VK_FILTER_NEAREST;
    samplerInfo.minFilter = VK_FILTER_NEAREST;
    samplerInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_NEAREST;
    samplerInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
    samplerInfo.addressModeV = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
    samplerInfo.addressModeW = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
    samplerInfo.mipLodBias = 0.0f;
    samplerInfo.anisotropyEnable = VK_FALSE;
    samplerInfo.maxAnisotropy = 1;
    samplerInfo.compareOp = VK_COMPARE_OP_NEVER;
    samplerInfo.minLod = 0.0f;
    samplerInfo.maxLod = 0.0f;
    samplerInfo.borderColor = VK_BORDER_COLOR_FLOAT_OPAQUE_WHITE;
    samplerInfo.unnormalizedCoordinates = VK_FALSE;

    auto err = vkCreateSampler(renderer->getDevice(), &samplerInfo, nullptr, &sampler);
    assert(!err);
}

void VulkanTexImpl::initDescriptorSet(VulkanRenderer* renderer)
{
    VkDescriptorSetAllocateInfo allocInfo = {};
    allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    allocInfo.descriptorPool = renderer->getPool().getPool();
    allocInfo.descriptorSetCount = 1;
    allocInfo.pSetLayouts = &renderer->getDescSetLayouts()[1];

    auto err = vkAllocateDescriptorSets(renderer->getDevice(), &allocInfo, &descriptorSet);
    assert(!err);

    VkDescriptorImageInfo descriptorImageInfo = {};
    descriptorImageInfo.imageView = imageView;
    descriptorImageInfo.sampler = sampler;
    descriptorImageInfo.imageLayout = VK_IMAGE_LAYOUT_GENERAL;

    VkWriteDescriptorSet write = {};
    write.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    write.dstSet = descriptorSet;
    write.dstBinding = 0;
    write.descriptorCount = 1;
    write.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    write.pImageInfo = &descriptorImageInfo;

    vkUpdateDescriptorSets(renderer->getDevice(), 1, &write, 0, nullptr);
}
