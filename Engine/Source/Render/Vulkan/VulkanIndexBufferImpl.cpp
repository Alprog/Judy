
#include "VulkanIndexBufferImpl.h"
#include <VulkanRenderer.h>
#include <cassert>

Impl<IndexBuffer, RendererType::Vulkan>::Impl(VulkanRenderer* renderer, IndexBuffer* ib)
{
    const UINT indexBufferSize = ib->indices.size() * sizeof(uint32_t);

    VkBufferCreateInfo vbInfo = {};
    vbInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    vbInfo.size = indexBufferSize;
    vbInfo.usage = VK_BUFFER_USAGE_INDEX_BUFFER_BIT;

    auto device = renderer->getDevice();

    auto err = vkCreateBuffer(device, &vbInfo, nullptr, &buffer);
    assert(!err);

    VkMemoryRequirements memoryRequirements = {};
    vkGetBufferMemoryRequirements(device, buffer, &memoryRequirements);

    VkMemoryAllocateInfo allocateInfo = {};
    allocateInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocateInfo.allocationSize = memoryRequirements.size;
    allocateInfo.memoryTypeIndex = renderer->getMemoryTypeIndex(memoryRequirements, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT);

    VkDeviceMemory vertexBufferMemory;
    err = vkAllocateMemory(device, &allocateInfo, nullptr, &vertexBufferMemory);
    assert(!err);

    void* data;
    err = vkMapMemory(device, vertexBufferMemory, 0, VK_WHOLE_SIZE, 0, &data);
    assert(!err);
    memcpy(data, &ib->indices[0], indexBufferSize);
    vkUnmapMemory(device, vertexBufferMemory);

    err = vkBindBufferMemory(device, buffer, vertexBufferMemory, 0);
    assert(!err);
}
