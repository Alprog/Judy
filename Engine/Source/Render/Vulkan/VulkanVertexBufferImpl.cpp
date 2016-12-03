
#include "VulkanVertexBufferImpl.h"

#include <VulkanRenderer.h>

Impl<VertexBuffer, RendererType::Vulkan>::Impl(VulkanRenderer* renderer, VertexBuffer* vb)
{
    const UINT vertexBufferSize = sizeof(Vertex) * vb->vertices.size();

    VkBufferCreateInfo vbInfo = {};
    vbInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    vbInfo.size = vertexBufferSize;
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

    void* data;
    err = vkMapMemory(device, vertexBufferMemory, 0, VK_WHOLE_SIZE, 0, &data);
    assert(!err);
    memcpy(data, &vb->vertices[0], vertexBufferSize);
    vkUnmapMemory(device, vertexBufferMemory);

    err = vkBindBufferMemory(device, buffer, vertexBufferMemory, 0);
    assert(!err);
}
