
#pragma once

#include "../IRenderer.h"

#include <vulkaninc.h>

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

    virtual void render(std::vector<RenderCommand> commands, RenderTarget* target) override;
    virtual void draw(RenderCommand renderCommand) override;
    virtual void clear(Color color) override;

protected:
    void init();
    void destroy();

    void initInstance();
    void initDevice();
    void initCommandBuffers();
    void initVertexBuffer();
    void initShaders();

    void checkLayers(std::vector<const char*>& names);
    void checkExtensions(std::vector<const char*>& names);

    RenderTargetContext& getContext(RenderTarget* renderTarget);
    VkSurfaceKHR createSurface(RenderTarget* renderTarget);
    VkSwapchainKHR createSwapChain(RenderTarget* renderTarget);
    void initPresentImages(RenderTargetContext& context);
    void initDepthBuffer(RenderTargetContext& context);
    void initRenderPass(RenderTargetContext& context);
    void initFrameBuffers(RenderTargetContext& context);
    void initPipeline(RenderTargetContext& context);

    void drawHelper(RenderTargetContext& context);
    VkShaderModule getShaderModule(std::string fileName);

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

    void sumbitCommamdsToQueue(VkCommandBuffer& commandBuffer, VkQueue& queue, VkSemaphore& semaphore);

    void resourceBarrier(VkImage& image, VkImageLayout oldStage, VkImageLayout newStage,
                         VkAccessFlagBits srcAccess, VkAccessFlagBits dstAccess);

    std::unordered_map<RenderTarget*, RenderTargetContext> contexts;

    uint32_t getMemoryTypeIndex(VkMemoryRequirements& requirements, VkMemoryPropertyFlags flags);

    template <typename T>
    void getInstanceProcAddr(T& funcPointer, const char* funcName);

    PFN_vkGetPhysicalDeviceSurfaceFormatsKHR getPhysicalDeviceSurfaceFormats = nullptr;
    PFN_vkGetPhysicalDeviceSurfaceCapabilitiesKHR getPhysicalDeviceSurfaceCapabilities = nullptr;

    PFN_vkCreateDebugReportCallbackEXT regDebugExt;
    PFN_vkDestroyDebugReportCallbackEXT unregDebugExt;
    VkDebugReportCallbackEXT debugExtension;
};
