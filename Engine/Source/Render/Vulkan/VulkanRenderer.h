
#pragma once

#include "../Renderer.h"
#include "../RendererBase.h"

#include "vulkan.h"

#include "VulkanShaderImpl.h"
#include "VulkanTextureImpl.h"
#include "VulkanIndexBufferImpl.h"
#include "VulkanVertexBufferImpl.h"
#include "VulkanConstantBufferImpl.h"

class VulkanRenderer : public RendererBase<VulkanRenderer>
{
public:
    static const RendererType rendererType = RendererType::Vulkan;

    VulkanRenderer();

    virtual void Render(std::vector<RenderCommand> commands, RenderTarget* target) override;
    virtual void Draw(RenderCommand renderCommand) override;
    virtual void Clear(Color color) override;

protected:
    void Init();

    VkInstance vulkanInstance;
};
