
#include "VulkanVertexBufferImpl.h"

#include <VulkanRenderer.h>
#include <cassert>

Impl<VertexBuffer, RendererType::Vulkan>::Impl(VulkanRenderer* renderer, VertexBuffer* resource)
{
    VkBufferCreateInfo vbInfo = {};
    vbInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    vbInfo.size = sizeof(VulkanTestVertex) * 3;
    vbInfo.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
    vbInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

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

    void* mapped;
    err = vkMapMemory(device, vertexBufferMemory, 0, VK_WHOLE_SIZE, 0, &mapped);
    assert(!err);

    VulkanTestVertex* triangle = (VulkanTestVertex*)mapped;
    triangle[0] = { -1.0f, -1.0f, 0, 0.0f, 0.0f };
    triangle[1] = {  1.0f, -1.0f, 0, 0.0f, 0.0f };
    triangle[2] = {  0.0f,  1.0f, 0, 0.0f, 0.0f };

    vkUnmapMemory(device, vertexBufferMemory);

    err = vkBindBufferMemory(device, buffer, vertexBufferMemory, 0);
    assert(!err);
}
