
#pragma once

#include "vulkan.h"
#include "../Impl.h"

class VulkanRenderer;
class ConstantBuffer;

template <>
class Impl<ConstantBuffer, RendererType::Vulkan>
{
public:
    Impl(VulkanRenderer* renderer, ConstantBuffer* resource);
};
