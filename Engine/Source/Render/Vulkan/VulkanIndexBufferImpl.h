
#pragma once

#include "vulkan.h"
#include "../Impl.h"

class VulkanRenderer;
class IndexBuffer;

template <>
class Impl<IndexBuffer, RendererType::Vulkan>
{
public:
    Impl(VulkanRenderer* renderer, IndexBuffer* resource);
};
