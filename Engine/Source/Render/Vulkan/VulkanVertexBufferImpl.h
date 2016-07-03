
#pragma once

#include "vulkan.h"
#include "../Impl.h"

class VulkanRenderer;
class VertexBuffer;

template <>
class Impl<VertexBuffer, RendererType::Vulkan>
{
public:
    Impl(VulkanRenderer* renderer, VertexBuffer* resource);
};
