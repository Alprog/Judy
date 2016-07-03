
#pragma once

#include "vulkan.h"
#include "../Impl.h"

class VulkanRenderer;
class Shader;

template <>
class Impl<Shader, RendererType::Vulkan>
{
public:
    Impl(VulkanRenderer* renderer, Shader* resource);
};
