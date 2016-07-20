
#include "VulkanRenderer.h"
#include <cassert>
#include "Platforms.h"

VulkanRenderer::VulkanRenderer()
{
    Init();
}

void VulkanRenderer::Draw(RenderCommand renderCommand)
{

}

void VulkanRenderer::Clear(Color color)
{

}

VKAPI_ATTR VkBool32 VKAPI_CALL
DebugCallback(VkFlags msgFlags, VkDebugReportObjectTypeEXT objType, uint64_t srcObject, size_t location,
              int32_t msgCode, const char* pLayerPrefix, const char* pMsg, void* pUserData)
{
    return false;
}

void VulkanRenderer::Init()
{
    InitInstance();
    InitDevice();
    InitCommandBuffers();
}

template <typename T>
void VulkanRenderer::GetInstanceProcAddr(T& funcPointer, const char* funcName)
{
    funcPointer = (T)vkGetInstanceProcAddr(vulkanInstance, funcName);
    assert(funcPointer);
}

void VulkanRenderer::InitInstance()
{
    VkApplicationInfo appInfo = {};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pNext = nullptr;
    appInfo.pApplicationName = "Unknown";
    appInfo.pEngineName = "Judy";
    appInfo.engineVersion = 1;
    appInfo.apiVersion = VK_API_VERSION_1_0;

    VkInstanceCreateInfo instanceInfo;
    instanceInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    instanceInfo.pNext = nullptr;
    instanceInfo.pApplicationInfo = &appInfo;

    std::vector<const char*> layers = { "VK_LAYER_LUNARG_standard_validation" };
    CheckLayers(layers);
    instanceInfo.enabledLayerCount = layers.size();
    instanceInfo.ppEnabledLayerNames = &layers[0];

    std::vector<const char*> extensions = { "VK_KHR_win32_surface", "VK_KHR_surface", "VK_EXT_debug_report" };
    CheckExtensions(extensions);
    instanceInfo.enabledExtensionCount = extensions.size();
    instanceInfo.ppEnabledExtensionNames = &extensions[0];

    auto err = vkCreateInstance(&instanceInfo, nullptr, &vulkanInstance);
    if (err)
    {
        exit(err);
    }

    GetInstanceProcAddr(regDebugExt, "vkCreateDebugReportCallbackEXT");
    GetInstanceProcAddr(unregDebugExt, "vkDestroyDebugReportCallbackEXT");
    GetInstanceProcAddr(getPhysicalDeviceSurfaceFormats, "vkGetPhysicalDeviceSurfaceFormatsKHR");
    GetInstanceProcAddr(getPhysicalDeviceSurfaceCapabilities, "vkGetPhysicalDeviceSurfaceCapabilitiesKHR");


    VkDebugReportCallbackCreateInfoEXT debugInfo;
    debugInfo.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CREATE_INFO_EXT;
    debugInfo.flags = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT;
    debugInfo.pfnCallback = DebugCallback;
    debugInfo.pUserData = nullptr;
    debugInfo.pNext = nullptr;
    err = regDebugExt(vulkanInstance, &debugInfo, nullptr, &debugExtension);

    if (err)
    {
        exit(err);
    }
}

VkSurfaceKHR VulkanRenderer::CreateSurface(RenderTarget* renderTarget)
{
    VkWin32SurfaceCreateInfoKHR surfaceInfo = {};
    surfaceInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
    surfaceInfo.pNext = nullptr;
    surfaceInfo.flags = 0;
    surfaceInfo.hinstance = static_cast<PlatformRenderTarget*>(renderTarget)->hInstance;
    surfaceInfo.hwnd = static_cast<PlatformRenderTarget*>(renderTarget)->hWnd;

    VkSurfaceKHR surface;

    auto err = vkCreateWin32SurfaceKHR(vulkanInstance, &surfaceInfo, nullptr, &surface);
    assert(!err);

    return surface;
}

void VulkanRenderer::InitDevice()
{
    uint32_t count = 0;
    vkEnumeratePhysicalDevices(vulkanInstance, &count, NULL);

    if (count > 0)
    {
        VkPhysicalDevice* physicalDevices = new VkPhysicalDevice[count];
        vkEnumeratePhysicalDevices(vulkanInstance, &count, physicalDevices);
        gpu = physicalDevices[0];
        delete[] physicalDevices;
    }

    queueFamilyIndex = 0; // hardcoded

    VkDeviceQueueCreateInfo queueInfo = {};
    queueInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queueInfo.queueFamilyIndex = queueFamilyIndex;
    queueInfo.queueCount = 1;
    float priorities[] = { 0.0f };
    queueInfo.pQueuePriorities = priorities;

    VkDeviceCreateInfo deviceInfo = {};
    deviceInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    deviceInfo.pNext = nullptr;
    deviceInfo.queueCreateInfoCount = 1;
    deviceInfo.pQueueCreateInfos = &queueInfo;

    std::vector<const char*> layers = { "VK_LAYER_LUNARG_standard_validation" };
    deviceInfo.enabledLayerCount = layers.size();
    deviceInfo.ppEnabledLayerNames = &layers[0];

    std::vector<const char*> extensions = { "VK_KHR_swapchain" };
    deviceInfo.enabledExtensionCount = extensions.size();
    deviceInfo.ppEnabledExtensionNames = &extensions[0];

    VkPhysicalDeviceFeatures features = {};
    features.shaderClipDistance = VK_TRUE;
    deviceInfo.pEnabledFeatures = &features;

    auto err = vkCreateDevice(gpu, &deviceInfo, nullptr, &device);
    assert(!err);

    vkGetPhysicalDeviceMemoryProperties(gpu, &gpuMemoryProperties);

    vkGetDeviceQueue(device, queueFamilyIndex, 0, &queue);
}

void VulkanRenderer::InitCommandBuffers()
{
    VkCommandPoolCreateInfo poolInfo = {};
    poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
    poolInfo.queueFamilyIndex = this->queueFamilyIndex;

    VkCommandPool commandPool;
    auto err = vkCreateCommandPool(device, &poolInfo, nullptr, &commandPool);
    assert(!err);

    VkCommandBufferAllocateInfo allocationInfo = {};
    allocationInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocationInfo.commandPool = commandPool;
    allocationInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocationInfo.commandBufferCount = 1;

    err = vkAllocateCommandBuffers(device, &allocationInfo, &setupCommandBuffer);
    assert(!err);

    err = vkAllocateCommandBuffers(device, &allocationInfo, &drawCommandBuffer);
    assert(!err);
}

VkSwapchainKHR VulkanRenderer::CreateSwapChain(RenderTarget* renderTarget)
{
    auto surface = CreateSurface(renderTarget);

    uint32_t count;
    auto err = getPhysicalDeviceSurfaceFormats(gpu, surface, &count, nullptr);
    assert(!err && count > 0);
    VkSurfaceFormatKHR* formats = new VkSurfaceFormatKHR[count];

    err = getPhysicalDeviceSurfaceFormats(gpu, surface, &count, formats);

    auto colorFormat = formats[0].format;
    VkColorSpaceKHR colorSpace = formats[0].colorSpace;
    if (colorFormat == VK_FORMAT_UNDEFINED)
    {
        colorFormat = VK_FORMAT_B8G8R8A8_UNORM;
    }

    VkSurfaceCapabilitiesKHR capabilities;
    err = getPhysicalDeviceSurfaceCapabilities(gpu, surface, &capabilities);
    assert(!err);

    auto size = renderTarget->GetSize();

    auto w = capabilities.currentExtent.width;
    auto h = capabilities.currentExtent.height;
    assert(w == size.x && h == size.y);

    VkPresentModeKHR swapchainPresentMode = VK_PRESENT_MODE_MAILBOX_KHR;

    uint32_t imageCount = capabilities.minImageCount + 1;
    if (capabilities.maxImageCount != 0)
    {
        imageCount = min(imageCount, capabilities.maxImageCount);
    }

    VkSwapchainCreateInfoKHR swapChainInfo = {};
    swapChainInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    swapChainInfo.surface = surface;
    swapChainInfo.minImageCount = imageCount;
    swapChainInfo.imageFormat = colorFormat;
    swapChainInfo.imageColorSpace = colorSpace;
    swapChainInfo.imageExtent = capabilities.currentExtent;
    swapChainInfo.imageArrayLayers = 1;
    swapChainInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
    swapChainInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
    swapChainInfo.preTransform = capabilities.currentTransform;
    swapChainInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    swapChainInfo.presentMode = swapchainPresentMode;
    swapChainInfo.clipped = true;

    VkSwapchainKHR swapChain;
    err = vkCreateSwapchainKHR(device, &swapChainInfo, nullptr, &swapChain);
    assert(!err);

    return swapChain;
}

void VulkanRenderer::InitPresentImages(RenderTargetContext& context)
{
    auto err = vkGetSwapchainImagesKHR(device, context.swapChain, &context.imageCount, nullptr);
    assert(!err);

    context.presentImages = new VkImage[context.imageCount];
    err = vkGetSwapchainImagesKHR(device, context.swapChain, &context.imageCount, context.presentImages);
    assert(!err);

    context.presentImageViews = new VkImageView[context.imageCount];

    for (auto i = 0; i < context.imageCount; i++)
    {
        VkImageViewCreateInfo viewInfo = {};
        viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
        viewInfo.pNext = nullptr;
        viewInfo.format = context.colorFormat;

        viewInfo.components =
        {
           VK_COMPONENT_SWIZZLE_R,
           VK_COMPONENT_SWIZZLE_G,
           VK_COMPONENT_SWIZZLE_B,
           VK_COMPONENT_SWIZZLE_A
        };

        viewInfo.subresourceRange = {VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1};
        viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
        viewInfo.flags = 0;
        viewInfo.image = context.presentImages[i];

        err = vkCreateImageView(device, &viewInfo, nullptr, &context.presentImageViews[i]);
        assert(!err);
    }

    context.bufferIndex = 0;
}

void VulkanRenderer::Destroy()
{
    unregDebugExt(vulkanInstance, debugExtension, nullptr);
}

void FilterNames(std::vector<const char*>& names, std::unordered_set<std::string>& allowNames)
{
    auto it = std::begin(names);
    while (it != std::end(names))
    {
        if (allowNames.find(*it) == std::end(allowNames))
        {
            it = names.erase(it);
            continue;
        }
        it++;
    }
}

void VulkanRenderer::CheckLayers(std::vector<const char*>& names)
{
    std::unordered_set<std::string> set;

    uint32_t count = 0;
    vkEnumerateInstanceLayerProperties(&count, nullptr);
    if (count > 0)
    {
        auto layerProperties = new VkLayerProperties[count];
        vkEnumerateInstanceLayerProperties(&count, layerProperties);
        for (int i = 0; i <= count; i++)
        {
            set.insert(layerProperties[i].layerName);
        }
        delete[] layerProperties;
    }

    FilterNames(names, set);
}

void VulkanRenderer::CheckExtensions(std::vector<const char*>& names)
{
    std::unordered_set<std::string> set;

    uint32_t count = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &count, nullptr);
    if (count > 0)
    {
        auto extensionProperties = new VkExtensionProperties[count];
        vkEnumerateInstanceExtensionProperties(nullptr, &count, extensionProperties);
        for (int i = 0; i <= count; i++)
        {
            set.insert(extensionProperties[i].extensionName);
        }
        delete[] extensionProperties;
    }

    FilterNames(names, set);
}

void VulkanRenderer::ResourceBarrier(VkImage& image, VkImageLayout oldStage, VkImageLayout newStage,
                                     VkAccessFlagBits srcAccess, VkAccessFlagBits dstAccess)
{
    VkImageMemoryBarrier barrier = {};
    barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
    barrier.pNext = nullptr;
    barrier.srcAccessMask = srcAccess;
    barrier.dstAccessMask = dstAccess;
    barrier.oldLayout = oldStage;
    barrier.newLayout = newStage;
    barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    barrier.image = image;
    barrier.subresourceRange = {VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1};
    vkCmdPipelineBarrier(drawCommandBuffer, VK_PIPELINE_STAGE_ALL_COMMANDS_BIT, VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT, 0, 0, nullptr, 0, nullptr, 1, &barrier);
}

void VulkanRenderer::InitDepthBuffer(RenderTargetContext& context)
{
    VkImageCreateInfo imageInfo = {};
    imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    imageInfo.pNext = nullptr;
    imageInfo.imageType = VK_IMAGE_TYPE_2D;
    imageInfo.format = context.depthFormat;
    imageInfo.extent = {context.width, context.height, 1};
    imageInfo.mipLevels = 1;
    imageInfo.arrayLayers = 1;
    imageInfo.samples = VK_SAMPLE_COUNT_1_BIT;
    imageInfo.tiling = VK_IMAGE_TILING_OPTIMAL;
    imageInfo.usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;
    imageInfo.flags = 0;

    auto err = vkCreateImage(device, &imageInfo, nullptr, &context.depthImage);
    assert(!err);

    //------------

    VkMemoryRequirements memoryRequirements;
    vkGetImageMemoryRequirements(device, context.depthImage, &memoryRequirements);

    VkMemoryAllocateInfo allocateInfo = {};
    allocateInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocateInfo.allocationSize = memoryRequirements.size;

    uint32_t memoryTypeBits = memoryRequirements.memoryTypeBits;
    VkMemoryPropertyFlags desiredMemoryFlags = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;
    for (int i = 0; i < 32; ++i)
    {
        VkMemoryType memoryType = gpuMemoryProperties.memoryTypes[i];
        if (memoryTypeBits & 1)
        {
            if ((memoryType.propertyFlags & desiredMemoryFlags) == desiredMemoryFlags)
            {
                allocateInfo.memoryTypeIndex = i;
                break;
            }
        }
        memoryTypeBits = memoryTypeBits >> 1;
    }

    VkDeviceMemory deviceMemory = {};
    err = vkAllocateMemory(device, &allocateInfo, nullptr, &deviceMemory);
    assert(!err);

    err = vkBindImageMemory(device, context.depthImage, deviceMemory, 0);
    assert(!err);

    //---------------

    VkImageViewCreateInfo viewInfo = {};
    viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    viewInfo.pNext = nullptr;
    viewInfo.format = context.depthFormat;
    viewInfo.subresourceRange = {VK_IMAGE_ASPECT_DEPTH_BIT, 0, 1, 0, 1};
    viewInfo.flags = 0;
    viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
    viewInfo.image = context.depthImage;

    err = vkCreateImageView(device, &viewInfo, nullptr, &context.depthImageView);
    assert(!err);
}

void VulkanRenderer::DrawHelper(RenderTargetContext& context)
{
    VkCommandBufferBeginInfo beginInfo = {};
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

    vkBeginCommandBuffer(drawCommandBuffer, &beginInfo);
    ResourceBarrier(context.presentImages[context.bufferIndex], VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL, (VkAccessFlagBits)0, VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT);

    VkClearValue clear_values[2] = {};
    clear_values[0].color = {0.2f, 1.0f, 0.2f, 1.0f};
    clear_values[1].depthStencil = {0, 0};

    VkRenderPassBeginInfo rpBeginInfo = {};
    rpBeginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    rpBeginInfo.pNext = nullptr;
    rpBeginInfo.renderPass = context.renderPass;
    rpBeginInfo.framebuffer = context.frameBuffers[context.bufferIndex];
    rpBeginInfo.renderArea.offset.x = 0;
    rpBeginInfo.renderArea.offset.y = 0;
    rpBeginInfo.renderArea.extent.width = context.width;
    rpBeginInfo.renderArea.extent.height = context.height;
    rpBeginInfo.clearValueCount = 1; // <---------- !
    rpBeginInfo.pClearValues = clear_values;

    auto a = drawCommandBuffer;
    vkCmdBeginRenderPass(drawCommandBuffer, &rpBeginInfo, VK_SUBPASS_CONTENTS_INLINE);

    vkCmdEndRenderPass(drawCommandBuffer);


    ResourceBarrier(context.presentImages[context.bufferIndex], VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL, VK_IMAGE_LAYOUT_PRESENT_SRC_KHR, VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT, VK_ACCESS_MEMORY_READ_BIT);
    vkEndCommandBuffer(drawCommandBuffer);
}

void VulkanRenderer::InitRenderPass(RenderTargetContext& context)
{
    VkAttachmentDescription attachments[2] = {};
    attachments[0].format = context.colorFormat;
    attachments[0].samples = VK_SAMPLE_COUNT_1_BIT;
    attachments[0].loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    attachments[0].storeOp = VK_ATTACHMENT_STORE_OP_STORE;
    attachments[0].stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    attachments[0].stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    attachments[0].initialLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
    attachments[0].finalLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

    attachments[1].format = context.depthFormat;
    attachments[1].samples = VK_SAMPLE_COUNT_1_BIT;
    attachments[1].loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    attachments[1].storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    attachments[1].stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    attachments[1].stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    attachments[1].initialLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
    attachments[1].finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

    VkAttachmentReference colorReference = {};
    colorReference.attachment = 0;
    colorReference.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

    VkAttachmentReference depthReference = {};
    depthReference.attachment = 1;
    depthReference.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

    VkSubpassDescription subpass = {};
    subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
    subpass.flags = 0;
    subpass.inputAttachmentCount = 0;
    subpass.pInputAttachments = nullptr;
    subpass.colorAttachmentCount = 1;
    subpass.pColorAttachments = &colorReference;
    subpass.pResolveAttachments = nullptr;
    subpass.pDepthStencilAttachment = nullptr; // &depthReference;  // <---------- !
    subpass.preserveAttachmentCount = 0;
    subpass.pPreserveAttachments = nullptr;

    VkRenderPassCreateInfo renderPassInfo = {};
    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    renderPassInfo.pNext = nullptr;
    renderPassInfo.attachmentCount = 1;  // <---------- !
    renderPassInfo.pAttachments = attachments;
    renderPassInfo.subpassCount = 1;
    renderPassInfo.pSubpasses = &subpass;
    renderPassInfo.dependencyCount = 0;
    renderPassInfo.pDependencies = nullptr;

    auto err = vkCreateRenderPass(device, &renderPassInfo, nullptr, &context.renderPass);
    assert(!err);
}

void VulkanRenderer::InitFrameBuffers(RenderTargetContext& context)
{
    VkImageView attachments[2];
    attachments[1] = context.depthImageView;

    VkFramebufferCreateInfo frameBufferInfo = {};
    frameBufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
    frameBufferInfo.renderPass = context.renderPass;
    frameBufferInfo.attachmentCount = 1;  // <---------- !
    frameBufferInfo.pAttachments = attachments;
    frameBufferInfo.width = context.width;
    frameBufferInfo.height = context.height;
    frameBufferInfo.layers = 1;

    context.frameBuffers = new VkFramebuffer[context.imageCount];
    for (auto i = 0; i < context.imageCount; i++)
    {
        attachments[0] = context.presentImageViews[i];
        auto err = vkCreateFramebuffer(device, &frameBufferInfo, nullptr, &context.frameBuffers[i]);
        assert(!err);
    }
}

void VulkanRenderer::SumbitCommamdsToQueue(VkCommandBuffer& commandBuffer, VkQueue& queue, VkSemaphore& semaphore)
{
    VkPipelineStageFlags stageFlags = VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT;
    VkSubmitInfo submitInfo = {};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submitInfo.pNext = nullptr;
    submitInfo.waitSemaphoreCount = 1;
    submitInfo.pWaitSemaphores = &semaphore;
    submitInfo.pWaitDstStageMask = &stageFlags,
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &commandBuffer;
    submitInfo.signalSemaphoreCount = 0;
    submitInfo.pSignalSemaphores = nullptr;

    auto err = vkQueueSubmit(queue, 1, &submitInfo, VK_NULL_HANDLE);
    assert(!err);
}

void VulkanRenderer::Render(std::vector<RenderCommand> commands, RenderTarget* target)
{
    RenderTargetContext& context = GetContext(target);

    VkSemaphore semaphore;
    VkSemaphoreCreateInfo semaphoreInfo = {};
    semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
    auto err = vkCreateSemaphore(device, &semaphoreInfo, nullptr, &semaphore);
    assert(!err);

    err = vkAcquireNextImageKHR(device, context.swapChain, UINT64_MAX, semaphore, VK_NULL_HANDLE, &context.bufferIndex);
    assert(!err);

    DrawHelper(context);
    SumbitCommamdsToQueue(drawCommandBuffer, queue, semaphore);

    VkPresentInfoKHR presentInfo = {};
    presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
    presentInfo.pNext = nullptr;
    presentInfo.waitSemaphoreCount = 0;
    presentInfo.pWaitSemaphores = nullptr;
    presentInfo.swapchainCount = 1;
    presentInfo.pSwapchains = &context.swapChain;
    presentInfo.pImageIndices = &context.bufferIndex;
    presentInfo.pResults = nullptr;
    err = vkQueuePresentKHR(queue, &presentInfo);
    assert(!err);

    err = vkQueueWaitIdle(queue);
    assert(!err);

    vkDestroySemaphore(device, semaphore, nullptr);
}

RenderTargetContext& VulkanRenderer::GetContext(RenderTarget* renderTarget)
{
    auto it = contexts.find(renderTarget);
    if (it != std::end(contexts))
    {
        return it->second;
    }
    else
    {
        RenderTargetContext context = {};
        auto size = renderTarget->GetSize();
        context.width = size.x;
        context.height = size.y;
        context.colorFormat = VK_FORMAT_B8G8R8A8_UNORM;
        context.depthFormat = VK_FORMAT_D16_UNORM;

        context.swapChain = CreateSwapChain(renderTarget);
        InitPresentImages(context);
        //InitDepthBuffer(context);
        InitRenderPass(context);
        InitFrameBuffers(context);

        contexts[renderTarget] = context;
        return contexts[renderTarget];
    }
}
