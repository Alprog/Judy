
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

    VkFormat format = formats[0].format;
    VkColorSpaceKHR colorSpace = formats[0].colorSpace;
    if (format == VK_FORMAT_UNDEFINED)
    {
        format = VK_FORMAT_B8G8R8A8_UNORM;
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
    swapChainInfo.imageFormat = format;
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

    //----------------

    err = vkGetSwapchainImagesKHR(device, swapChain, &imageCount, nullptr);
    assert(!err);

    auto swapchainImages = new VkImage[imageCount];
    err = vkGetSwapchainImagesKHR(device, swapChain, &imageCount, swapchainImages);


    buffers = new SwapchainBuffers[imageCount];
    assert(buffers);

    for (auto i = 0; i < imageCount; i++)
    {
        VkImageViewCreateInfo viewInfo = {};
        viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
        viewInfo.pNext = nullptr;
        viewInfo.format = format;

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
        viewInfo.image =  swapchainImages[i];

        buffers[i].image = swapchainImages[i];
        err = vkCreateImageView(device, &viewInfo, nullptr, &buffers[i].view);
        assert(!err);
    }

    bufferIndex = 0;

    return swapChain;
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

void VulkanRenderer::DrawHelper()
{
    VkCommandBufferBeginInfo beginInfo = {};
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
    vkBeginCommandBuffer(drawCommandBuffer, &beginInfo);

    VkImageMemoryBarrier barrier = {};
    barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
    barrier.pNext = nullptr;
    barrier.srcAccessMask = 0;
    barrier.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
    barrier.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    barrier.newLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
    barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    barrier.image = buffers[bufferIndex].image;
    barrier.subresourceRange = {VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1};

    vkCmdPipelineBarrier(drawCommandBuffer, VK_PIPELINE_STAGE_ALL_COMMANDS_BIT, VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT, 0, 0, nullptr, 0, nullptr, 1, &barrier);

    vkEndCommandBuffer(drawCommandBuffer);
}

void VulkanRenderer::Render(std::vector<RenderCommand> commands, RenderTarget* target)
{
    VkSwapchainKHR swapChain = GetSwapChain(target);

    VkSemaphore semaphore;
    VkSemaphoreCreateInfo semaphoreInfo = {};
    semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
    auto err = vkCreateSemaphore(device, &semaphoreInfo, nullptr, &semaphore);
    assert(!err);

    err = vkAcquireNextImageKHR(device, swapChain, UINT64_MAX, semaphore, NULL, &bufferIndex);
    assert(!err);

    DrawHelper();

    VkPresentInfoKHR presentInfo = {};
    presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
    presentInfo.pNext = nullptr;
    presentInfo.waitSemaphoreCount = 0;
    presentInfo.pWaitSemaphores = nullptr;
    presentInfo.swapchainCount = 1;
    presentInfo.pSwapchains = &swapChain;
    presentInfo.pImageIndices = &bufferIndex;
    presentInfo.pResults = NULL;
    vkQueuePresentKHR(queue, &presentInfo);


    vkDestroySemaphore(device, semaphore, nullptr);
}

VkSwapchainKHR VulkanRenderer::GetSwapChain(RenderTarget* renderTarget)
{
    auto it = swapChains.find(renderTarget);
    if (it != std::end(swapChains))
    {
        return it->second;
    }
    else
    {
        auto swapChain = CreateSwapChain(renderTarget);
        swapChains[renderTarget] = swapChain;
        return swapChain;
    }
}
