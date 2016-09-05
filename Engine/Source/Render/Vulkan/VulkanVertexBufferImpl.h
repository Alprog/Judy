
#pragma once

#include <vulkaninc.h>
#include "../Impl.h"
#include "../VertexBuffer.h"

class VulkanRenderer;

template <>
class Impl<VertexBuffer, RendererType::Vulkan>
{
public:
    Impl(VulkanRenderer* renderer, VertexBuffer* resource);
};
