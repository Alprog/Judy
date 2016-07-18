
#pragma once

#include "../IRenderer.h"

#include "vulkan.h"

#include "VulkanShaderImpl.h"
#include "VulkanTextureImpl.h"
#include "VulkanIndexBufferImpl.h"
#include "VulkanVertexBufferImpl.h"
#include "VulkanConstantBufferImpl.h"
#include "../Renderer.h"

struct SwapchainBuffers
{
    VkImage image;
    VkCommandBuffer cmd;
    VkImageView view;
};

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
    void InitDevice();
    void InitCommandBuffers();

    void DrawHelper();

    VkSurfaceKHR CreateSurface(RenderTarget* renderTarget);
    VkSwapchainKHR CreateSwapChain(RenderTarget* renderTarget);

    void CheckLayers(std::vector<const char*>& names);
    void CheckExtensions(std::vector<const char*>& names);

    VkSwapchainKHR GetSwapChain(RenderTarget* renderTarget);

    VkInstance vulkanInstance;
    VkDevice device;
    VkPhysicalDevice gpu;
    VkQueue queue;
    uint32_t queueFamilyIndex;
    VkCommandBuffer setupCommandBuffer;
    VkCommandBuffer drawCommandBuffer;
    uint32_t bufferIndex;
    SwapchainBuffers* buffers;

    std::unordered_map<RenderTarget*, VkSwapchainKHR> swapChains;

    template <typename T>
    void GetInstanceProcAddr(T& funcPointer, const char* funcName);

    PFN_vkGetPhysicalDeviceSurfaceFormatsKHR getPhysicalDeviceSurfaceFormats = nullptr;
    PFN_vkGetPhysicalDeviceSurfaceCapabilitiesKHR getPhysicalDeviceSurfaceCapabilities = nullptr;

    PFN_vkCreateDebugReportCallbackEXT regDebugExt;
    PFN_vkDestroyDebugReportCallbackEXT unregDebugExt;
    VkDebugReportCallbackEXT debugExtension;
};
