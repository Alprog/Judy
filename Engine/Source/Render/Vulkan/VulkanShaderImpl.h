
#pragma once

#include <vulkaninc.h>
#include "../Impl.h"
#include "../Shader.h"

class VulkanRenderer;

template <>
class Impl<Shader, RendererType::Vulkan>
{
public:
    Impl(VulkanRenderer* renderer, Shader* resource);
};
