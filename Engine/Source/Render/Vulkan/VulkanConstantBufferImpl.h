
#pragma once

#include "vulkan.h"
#include "../Impl.h"
#include "../ConstantBuffer.h"

class VulkanRenderer;

template <>
class Impl<ConstantBuffer, RendererType::Vulkan>
{
public:
    Impl(VulkanRenderer* renderer, ConstantBuffer* resource);
};
