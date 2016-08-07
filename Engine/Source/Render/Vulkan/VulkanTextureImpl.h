
#pragma once

#include "vulkan.h"
#include "../Impl.h"
#include "../Texture.h"

class VulkanRenderer;

template <>
class Impl<Texture, RendererType::Vulkan>
{
public:
    Impl(VulkanRenderer* renderer, Texture* resource);
};
