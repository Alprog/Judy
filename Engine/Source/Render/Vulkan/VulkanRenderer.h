
#pragma once

#include "../IRenderer.h"

#include "vulkan.h"

#include "VulkanShaderImpl.h"
#include "VulkanTextureImpl.h"
#include "VulkanIndexBufferImpl.h"
#include "VulkanVertexBufferImpl.h"
#include "VulkanConstantBufferImpl.h"
#include "../Renderer.h"

class VulkanRenderer : public Renderer<RendererType::Vulkan>
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
    void InitSurface();
    void InitDevice();
    void InitSwapChain();

    void CheckLayers(std::vector<const char*>& names);
    void CheckExtensions(std::vector<const char*>& names);

    VkInstance vulkanInstance;
    VkDevice device;
    VkPhysicalDevice gpu;
    VkSurfaceKHR surface;

    template <typename T>
    void GetInstanceProcAddr(T& funcPointer, const char* funcName);

    PFN_vkGetPhysicalDeviceSurfaceFormatsKHR getPhysicalDeviceSurfaceFormats = nullptr;

    PFN_vkCreateDebugReportCallbackEXT regDebugExt;
    PFN_vkDestroyDebugReportCallbackEXT unregDebugExt;
    VkDebugReportCallbackEXT debugExtension;
};
