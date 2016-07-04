
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
    void Destroy();

    void InitInstance();
    void InitDevice();

    void CheckLayers(std::vector<const char*>& names);
    void CheckExtensions(std::vector<const char*>& names);

    VkInstance vulkanInstance;
    VkDevice device;

    PFN_vkCreateDebugReportCallbackEXT regDebugExt;
    PFN_vkDestroyDebugReportCallbackEXT unregDebugExt;
    VkDebugReportCallbackEXT debugExtension;
};
