
#include "VulkanConstantBufferImpl.h"
#include <VulkanRenderer.h>

Impl<ConstantBuffer, RendererType::Vulkan>::Impl(VulkanRenderer* renderer, ConstantBuffer* cb)
    : resource{cb}
    , version{cb->version}
    , renderer{renderer}
{
    const UINT constantBufferSize = sizeof(cb->data);

    auto device = renderer->getDevice();

    VkBufferCreateInfo cbInfo = {};
    cbInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    cbInfo.size = constantBufferSize;
    cbInfo.usage = VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT;
    cbInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

    auto err = vkCreateBuffer(device, &cbInfo, nullptr, &buffer);
    assert(!err);

    VkMemoryRequirements memoryRequirements = {};
    vkGetBufferMemoryRequirements(device, buffer, &memoryRequirements);

    VkMemoryAllocateInfo allocateInfo = {};
    allocateInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocateInfo.allocationSize = memoryRequirements.size;
    auto flags = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;
    allocateInfo.memoryTypeIndex = renderer->getMemoryTypeIndex(memoryRequirements, flags);

    err = vkAllocateMemory(device, &allocateInfo, nullptr, &constantBufferMemory);
    assert(!err);

    void* data;
    err = vkMapMemory(device, constantBufferMemory, 0, VK_WHOLE_SIZE, 0, &data);
    assert(!err);
    memcpy(data, &cb->data, constantBufferSize);
    vkUnmapMemory(device, constantBufferMemory);

    err = vkBindBufferMemory(device, buffer, constantBufferMemory, 0);
    assert(!err);

    //-----------

    VkDescriptorBufferInfo descriptorBufferInfo = {};
    descriptorBufferInfo.buffer = buffer;
    descriptorBufferInfo.offset = 0;
    descriptorBufferInfo.range = constantBufferSize;

    //-----------

    VkDescriptorSetAllocateInfo descSetInfo = {};
    descSetInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    descSetInfo.descriptorPool = renderer->getPool().getPool();
    descSetInfo.descriptorSetCount = 1;
    descSetInfo.pSetLayouts = renderer->getDescSetLayouts();

    err = vkAllocateDescriptorSets(device, &descSetInfo, &descriptorSet);
    assert(!err);

    VkWriteDescriptorSet writeSetInfo = {};
    writeSetInfo.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    writeSetInfo.dstSet = descriptorSet;
    writeSetInfo.dstBinding = 0;
    writeSetInfo.descriptorCount = 1;
    writeSetInfo.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    writeSetInfo.pBufferInfo = &descriptorBufferInfo;

    vkUpdateDescriptorSets(device, 1, &writeSetInfo, 0, nullptr);
}

void Impl<ConstantBuffer, RendererType::Vulkan>::update()
{
    if (version < resource->version)
    {
        auto m = resource->data.MVP;

        resource->data.MVP = m * Matrix::Scaling({1, -1, 1});

        void* data;
        auto size = sizeof(resource->data);
        auto err = vkMapMemory(renderer->getDevice(), constantBufferMemory, 0, size, 0, &data);
        assert(!err);
        memcpy(data, &resource->data, size);
        vkUnmapMemory(renderer->getDevice(), constantBufferMemory);
        version = resource->version;

        resource->data.MVP = m;
    }
}
