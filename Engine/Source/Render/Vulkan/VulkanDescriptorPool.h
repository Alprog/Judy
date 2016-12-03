
#pragma once

#include <vulkaninc.h>

class VulkanDescriptorPool
{
public:
    VulkanDescriptorPool(VkDevice& device);

    inline VkDescriptorPool& getPool() { return pool; }

private:
    VkDescriptorPool pool;
};
