
#pragma once

#include "vulkan.h"
#include "../Impl.h"

class VulkanRenderer;
class Texture;

template <>
class Impl<Texture, RendererType::Vulkan>
{
public:
    Impl(VulkanRenderer* renderer, Texture* resource);
};
