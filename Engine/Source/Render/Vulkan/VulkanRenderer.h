
#pragma once

#include "../IRenderer.h"

#include "vulkan.h"

#include "VulkanShaderImpl.h"
#include "VulkanTextureImpl.h"
#include "VulkanIndexBufferImpl.h"
#include "VulkanVertexBufferImpl.h"
#include "VulkanConstantBufferImpl.h"
#include "../Renderer.h"

struct VulkanTestVertex
{
    float x, y, z, w;
};

struct RenderTargetContext
{
    uint32_t width;
    uint32_t height;
    VkFormat colorFormat;
    VkFormat depthFormat;

    VkSwapchainKHR swapChain;
    uint32_t imageCount;
    VkImage* presentImages;
    VkImageView* presentImageViews;
    uint32_t bufferIndex;

    VkImage depthImage;
    VkImageView depthImageView;

    VkRenderPass renderPass;
    VkFramebuffer* frameBuffers;

    VkPipeline pipeline;
    VkPipelineLayout pipelineLayout;
    VkDescriptorSet descriptorSet;
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
    void InitVertexBuffer();
    void InitShaders();

    void CheckLayers(std::vector<const char*>& names);
    void CheckExtensions(std::vector<const char*>& names);

    RenderTargetContext& GetContext(RenderTarget* renderTarget);
    VkSurfaceKHR CreateSurface(RenderTarget* renderTarget);
    VkSwapchainKHR CreateSwapChain(RenderTarget* renderTarget);
    void InitPresentImages(RenderTargetContext& context);
    void InitDepthBuffer(RenderTargetContext& context);
    void InitRenderPass(RenderTargetContext& context);
    void InitFrameBuffers(RenderTargetContext& context);
    void InitPipeline(RenderTargetContext& context);

    void DrawHelper(RenderTargetContext& context);
    VkShaderModule GetShaderModule(std::string fileName);

    VkInstance vulkanInstance;
    VkDevice device;
    VkPhysicalDevice gpu;
    VkPhysicalDeviceMemoryProperties gpuMemoryProperties;
    VkQueue queue;
    uint32_t queueFamilyIndex;
    VkCommandBuffer setupCommandBuffer;
    VkCommandBuffer drawCommandBuffer;

    VkShaderModule vertexShader;
    VkShaderModule fragmentShader;
    VkBuffer vertexBuffer;

    void SumbitCommamdsToQueue(VkCommandBuffer& commandBuffer, VkQueue& queue, VkSemaphore& semaphore);

    void ResourceBarrier(VkImage& image, VkImageLayout oldStage, VkImageLayout newStage,
                         VkAccessFlagBits srcAccess, VkAccessFlagBits dstAccess);

    std::unordered_map<RenderTarget*, RenderTargetContext> contexts;

    uint32_t GetMemoryTypeIndex(VkMemoryRequirements& requirements, VkMemoryPropertyFlags flags);

    template <typename T>
    void GetInstanceProcAddr(T& funcPointer, const char* funcName);

    PFN_vkGetPhysicalDeviceSurfaceFormatsKHR getPhysicalDeviceSurfaceFormats = nullptr;
    PFN_vkGetPhysicalDeviceSurfaceCapabilitiesKHR getPhysicalDeviceSurfaceCapabilities = nullptr;

    PFN_vkCreateDebugReportCallbackEXT regDebugExt;
    PFN_vkDestroyDebugReportCallbackEXT unregDebugExt;
    VkDebugReportCallbackEXT debugExtension;
};
