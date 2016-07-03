
#pragma once

#include "../Renderer.h"
#include "../RendererBase.h"

#include "VulkanShaderImpl.h"
#include "VulkanTextureImpl.h"
#include "VulkanIndexBufferImpl.h"
#include "VulkanVertexBufferImpl.h"
#include "VulkanConstantBufferImpl.h"

class VulkanRenderer : public RendererBase<VulkanRenderer>
{
public:
    static const RendererType rendererType = RendererType::Vulkan;
};
